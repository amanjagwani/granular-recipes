#include "granular_recipes/recipes/spectral_drift.h"
#include "granular_recipes/utils.h"

namespace gr
{
    void SpectralDriftRecipe::Init(float sr, uint32_t hopSize, uint32_t bufferDepth)
    {
        SpectralRecipe::Init(sr, hopSize, bufferDepth);
        rand_.Init(54321u);
        holdNorm_ = 0.3f;
        walkNorm_ = 0.0f;
        advancePerHop_ = 1.0f / static_cast<float>(bufferDepth);
    }

    void SpectralDriftRecipe::UpdateParamsFromEnergy()
    {
        params_.jitterRange = params_.energy;
    }

    void SpectralDriftRecipe::UpdateParamsFromIntensity()
    {
        float i = params_.intensity;
        params_.blurFrames = 1 + static_cast<uint16_t>(31.0f * i);
    }

    void SpectralDriftRecipe::OnSample()
    {
        float walkStep = params_.jitterRange * 0.002f;
        walkNorm_ += (2.0f * rand_.GetFloat() - 1.0f) * walkStep;
        walkNorm_ = utils::Clampf(walkNorm_, -0.5f, 0.5f);
    }

    void SpectralDriftRecipe::OnHop()
    {
        holdNorm_ += advancePerHop_;
        if (holdNorm_ > 0.8f)
            holdNorm_ = 0.1f + rand_.GetFloat() * 0.3f;

        
        float jitRange = params_.jitterRange;
        float randomPos = rand_.GetFloat();  
        float holdPos = holdNorm_ + walkNorm_ * jitRange;

        float lb = holdPos * (1.0f - jitRange * jitRange) + randomPos * (jitRange * jitRange);

        lb = utils::Clampf(lb, 0.0f, 1.0f);

        params_.setUnifiedLookback(lb);
        params_.pitchSt = 0.0f;
    }
}
