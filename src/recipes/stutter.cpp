#include "granular_recipes/recipes/stutter.h"
#include "granular_recipes/utils.h"
#include <algorithm>

namespace gr
{
    void StutterRecipe::Init(float sr, size_t bufSize)
    {
        Recipe::Init(sr, bufSize);
        params_.grainSizeS = 0.10f;
        params_.densityHz = 10.0f;
        params_.jitter = 0.0f;
        params_.jitterRange = 0.0f;
        params_.spread = 0.85f;
        params_.gain = 0.85f;
        params_.pitchSt = 0.0f;
        params_.feedback = 0.5f;
        params_.lookback = 0.20f;
        params_.reverse = false;
        params_.freeze = false;
        params_.densityJitter = 0.0f;

        rand_.Init();
        clock_.Init(sampleRate_, bpm_);
        clock_.SetSubdivisionFromIntensity(params_.intensity);

        holdOffsetSamps_ = 1000.0f;
        baseGrainSizeS_ = params_.grainSizeS;
        baseDensityHz_ = params_.densityHz;
        currentPitchSt_ = 0.0f;
        currentGrainSizeS_ = params_.grainSizeS;
        currentDensityHz_ = params_.densityHz;
        currentReverse_ = false;
    }

    void StutterRecipe::UpdateParamsFromEnergy()
    {
        const float energy = params_.energy;
        baseGrainSizeS_ = 0.22f - 0.19f * energy;
        baseDensityHz_ = 6.0f + 20.0f * energy;
    }

    void StutterRecipe::UpdateParamsFromIntensity()
    {
        clock_.SetSubdivisionFromIntensity(params_.intensity);
    }

    void StutterRecipe::OnSample()
    {
        if (clock_.Tick())
        {

            holdOffsetSamps_ = 500.0f + rand_.GetFloat() * 2000.0f;

            currentReverse_ = (rand_.GetFloat() < 0.30f);

            const float grainSizeVar = (0.4f * rand_.GetFloat()) - 0.2f;
            currentGrainSizeS_ = baseGrainSizeS_ * (1.0f + grainSizeVar);
            currentDensityHz_ = baseDensityHz_ * (1.0f - grainSizeVar);

            if (rand_.GetFloat() < 0.35f)
            {
                const size_t idx = static_cast<size_t>(rand_.GetFloat() * 5);
                currentPitchSt_ = pitches_[idx < 5 ? idx : 0];
            }
            else
            {
                currentPitchSt_ = 0.0f;
            }
        }

        holdOffsetSamps_ = std::min(holdOffsetSamps_ + 1.0f, static_cast<float>(bufSize_ - 1));
        const float lookbackNorm = holdOffsetSamps_ / static_cast<float>(bufSize_ - 1);

        params_.freeze = false;
        params_.lookback = utils::Clampf(lookbackNorm, 0.0f, 1.0f);
        params_.pitchSt = currentPitchSt_;
        params_.grainSizeS = currentGrainSizeS_;
        params_.reverse = currentReverse_;
        params_.densityHz = currentDensityHz_;
    }

    void StutterRecipe::OnSpawn()
    {
        // Empty — all decisions made on clock edge so grains within
        // a stutter period are identical.
    }

    void StutterRecipe::SetBpm(float bpm)
    {
        bpm_ = bpm;
        clock_.SetBpm(bpm);
    }

}
