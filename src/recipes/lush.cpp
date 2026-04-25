#include "granular_recipes/recipes/lush.h"
#include <algorithm>
#include <cmath>
#include "granular_recipes/utils.h"

namespace gr
{
    void LushRecipe::Init(float sr, size_t bufSize)
    {
        Recipe::Init(sr, bufSize);
        params_.grainSizeS = 0.18f;
        params_.densityHz = 18.0f;
        params_.jitter = 0.20f;
        params_.jitterRange = 0.02f;
        params_.spread = 0.90f;
        params_.gain = 0.85f;
        params_.pitchSt = 0.0f;
        params_.feedback = 0.0f;
        params_.densityJitter = 0.12f;

        scanCenter_ = 0.005f;
        scanDepth_ = 0.005f;
        scanRate_ = 0.05f;
        pitchShiftProb_ = 0.0f;
        pitchTier_ = 0;

        phasor_.Init(sr);
        phasor_.SetFreq(scanRate_);

        rand_.Init();
    }

    void LushRecipe::UpdateParamsFromEnergy()
    {
        const float energy = params_.energy;
        params_.grainSizeS = 0.60f - (0.55f * energy);
        params_.densityHz = 4.0f + (63.0f * energy);
        params_.jitter = 0.10f + (0.40f * energy);
        params_.jitterRange = 0.006f + (0.040f * energy);
    }

    void LushRecipe::UpdateParamsFromIntensity()
    {
        const float intens = params_.intensity;

        scanRate_ = 0.05f + 3.0f * intens * intens;
        phasor_.SetFreq(scanRate_);

        scanCenter_ = 0.005f + 0.25f * intens;
        scanDepth_ = 0.005f + 0.08f * intens;

        params_.feedback = 0.85f * intens * intens;

        if (intens < 0.25f)
        {
            pitchShiftProb_ = 0.0f;
            pitchTier_ = 0;
        }
        else if (intens < 0.55f)
        {
            pitchShiftProb_ = (intens - 0.25f) / 0.30f * 0.40f;
            pitchTier_ = 1;
        }
        else
        {
            pitchShiftProb_ = 0.40f + (intens - 0.55f) / 0.45f * 0.35f;
            pitchTier_ = 2;
        }
    }

    void LushRecipe::OnSpawn()
    {
        if (pitchTier_ > 0 && rand_.GetFloat() < pitchShiftProb_)
        {
            if (pitchTier_ == 2)
            {
                const size_t idx = static_cast<size_t>(rand_.GetFloat() * 6);
                params_.pitchSt = fullStack_[idx < 6 ? idx : 0];
            }
            else
            {
                const size_t idx = static_cast<size_t>(rand_.GetFloat() * 2);
                params_.pitchSt = fifths_[idx < 2 ? idx : 0];
            }
        }
        else
        {
            params_.pitchSt = 0.0f;
        }

        if (rand_.GetFloat() < 0.20f)
        {
            params_.reverse = !params_.reverse;
        }
    }

    void LushRecipe::OnSample()
    {
        float phase = phasor_.Process();
        const float pos = scanCenter_ + (scanDepth_ * (phase * 2.0f - 1.0f));
        params_.lookback = utils::Clampf(pos, 0.0f, 1.0f);
    }

}
