#include "granular_recipes/recipes/spectral_disperse.h"
#include "granular_recipes/utils.h"

namespace gr
{
    void SpectralDisperseRecipe::Init(float sr, uint32_t hopSize, uint32_t bufferDepth)
    {
        SpectralRecipe::Init(sr, hopSize, bufferDepth);
        rand_.Init(98765u);
        holdNorm_ = 0.3f;
        advancePerHop_ = 1.0f / static_cast<float>(bufferDepth);
        walkLo_ = 0.0f;
        walkMid_ = 0.0f;
        walkHi_ = 0.0f;
    }

    void SpectralDisperseRecipe::UpdateParamsFromEnergy()
    {
        const float e = params_.energy;
        spreadNorm_ = e * e;
        params_.jitterRange = 0.8f * e * e;
    }

    void SpectralDisperseRecipe::UpdateParamsFromIntensity()
    {
        params_.pitchSt = -12.0f + 36.0f * params_.intensity;
    }

    void SpectralDisperseRecipe::OnSample()
    {
        float walkStep = params_.jitterRange * 0.003f;
        walkLo_  += (2.0f * rand_.GetFloat() - 1.0f) * walkStep;
        walkMid_ += (2.0f * rand_.GetFloat() - 1.0f) * walkStep;
        walkHi_  += (2.0f * rand_.GetFloat() - 1.0f) * walkStep;

        walkLo_  = utils::Clampf(walkLo_,  -0.4f, 0.4f);
        walkMid_ = utils::Clampf(walkMid_, -0.4f, 0.4f);
        walkHi_  = utils::Clampf(walkHi_,  -0.4f, 0.4f);
    }

    void SpectralDisperseRecipe::OnHop()
    {
        holdNorm_ += advancePerHop_;
        if (holdNorm_ > 0.6f) holdNorm_ = 0.25f;

       
        float lbLo  = holdNorm_ + walkLo_ * spreadNorm_;
        float lbMid = holdNorm_ + spreadNorm_ * 0.5f + walkMid_ * spreadNorm_;
        float lbHi  = holdNorm_ + spreadNorm_ + walkHi_ * spreadNorm_;

        lbLo  += (2.0f * rand_.GetFloat() - 1.0f) * params_.jitterRange;
        lbMid += (2.0f * rand_.GetFloat() - 1.0f) * params_.jitterRange;
        lbHi  += (2.0f * rand_.GetFloat() - 1.0f) * params_.jitterRange;

        params_.lookbackLo  = utils::Clampf(lbLo,  0.0f, 1.0f);
        params_.lookbackMid = utils::Clampf(lbMid, 0.0f, 1.0f);
        params_.lookbackHi  = utils::Clampf(lbHi,  0.0f, 1.0f);
    }
}
