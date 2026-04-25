#include "granular_recipes/recipes/sprinkle.h"
#include <algorithm>
#include "granular_recipes/utils.h"

namespace gr
{
    void SprinkleRecipe::Init(float sr, size_t bufSize)
    {
        Recipe::Init(sr, bufSize);

        params_.grainSizeS = 0.052f;
        params_.densityHz = 3.0f;
        params_.jitter = 0.6f;
        params_.jitterRange = 0.05f;
        params_.spread = 0.50f;
        params_.gain = 0.80f;
        params_.pitchSt = 0.0f;
        params_.feedback = 0.0f;
        params_.lookback = 0.02f;
        params_.reverse = false;
        params_.densityJitter = 0.15f;

        posCenter_ = 0.02f;
        posDepth_ = 0.02f;
        holdRateHz_ = 0.6f;
        reverseProb_ = 0.05f;
        pitchShiftProb_ = 0.0f;

        rand_.Init();
        phasor_.Init(sr);
        phasor_.SetFreq(holdRateHz_);

        lastPhase_ = 0.0f;
    }

    void SprinkleRecipe::UpdateParamsFromEnergy()
    {
        const float energy = params_.energy;
        params_.grainSizeS = 0.20f - 0.164f * energy;
        params_.densityHz = 1.5f + 15.5f * energy;
        params_.jitter = 0.35f + 0.45f * energy;
        params_.jitterRange = 0.02f + 0.06f * energy;
    }

    void SprinkleRecipe::UpdateParamsFromIntensity()
    {
        const float intens = params_.intensity;

        params_.spread = 0.40f + 0.60f * intens;

        holdRateHz_ = 0.6f + 3.0f * intens;
        phasor_.SetFreq(holdRateHz_);

        posDepth_ = 0.01f + 0.06f * intens;

        reverseProb_ = 0.05f + 0.35f * intens;

        params_.densityJitter = 0.15f + 0.55f * intens;

        pitchShiftProb_ = intens > 0.2f ? (intens - 0.2f) / 0.8f * 0.50f : 0.0f;
    }

    void SprinkleRecipe::OnSpawn()
    {
        if (rand_.GetFloat() < pitchShiftProb_)
        {
            const size_t idx = static_cast<size_t>(rand_.GetFloat() * 5);
            params_.pitchSt = pitches_[idx < 5 ? idx : 0];
        }
        else
        {
            params_.pitchSt = 0.0f;
        }

        if (rand_.GetFloat() < reverseProb_)
        {
            params_.reverse = !params_.reverse;
        }
    }

    void SprinkleRecipe::OnSample()
    {
        float phase = phasor_.Process();
        if (phase < lastPhase_)
        {
            posCenter_ = 0.005f + 0.04f * rand_.GetFloat();
        }
        lastPhase_ = phase;
        const float randVal = 2.0f * rand_.GetFloat() - 1.0f;
        const float pos = posCenter_ + (posDepth_ * randVal);
        params_.lookback = utils::Clampf(pos, 0.0f, 1.0f);
    }
}
