#include "granular_recipes/recipes/cloud.h"
#include <algorithm>
#include "granular_recipes/utils.h"

namespace gr
{
    void CloudRecipe::Init(float sr, size_t bufSize)
    {
        Recipe::Init(sr, bufSize);
        params_.grainSizeS = 0.02f;
        params_.densityHz = 80.0f;
        params_.jitter = 0.45f;
        params_.jitterRange = 0.03f;
        params_.spread = 0.9f;
        params_.gain = 0.75f;
        params_.pitchSt = 0.0f;
        params_.feedback = 0.25f;
        params_.lookback = 0.25f;
        params_.reverse = false;
        params_.densityJitter = 0.35f;

        scanRate_ = 0.06f;
        scanDepth_ = 0.18f;

        phasor_.Init(sr);
        phasor_.SetFreq(scanRate_);
    }

    void CloudRecipe::UpdateParamsFromEnergy()
    {
        const float energy = params_.energy;
        params_.grainSizeS = 0.18f - 0.16f * energy;
        params_.densityHz = 30.0f + 90.0f * energy;
        params_.jitter = 0.20f + 0.50f * energy;
        params_.jitterRange = 0.02f + 0.06f * energy;

        scanRate_ = 0.02f + 0.18f * energy;
        phasor_.SetFreq(scanRate_);
    }

    void CloudRecipe::UpdateParamsFromIntensity()
    {
        const float intens = params_.intensity;
        params_.spread = 0.6f + 0.4f * intens;
        scanDepth_ = 0.08f + 0.25f * intens;
    }

    void CloudRecipe::OnSpawn()
    {
        if (rand_.GetFloat() < 0.1f)
        {
            params_.reverse = !params_.reverse;
        }
    }

    void CloudRecipe::OnSample()
    {
        float phase = phasor_.Process();
        float pos = 0.75f + (scanDepth_ * (phase * 2.0f - 1.0f));
        params_.lookback = utils::Clampf(pos, 0.0f, 1.0f);
    }
}
