#include "granular_recipes/recipes/spectral_stutter.h"
#include "granular_recipes/utils.h"

namespace gr
{
    void SpectralStutterRecipe::Init(float sr, uint32_t hopSize, uint32_t bufferDepth)
    {
        SpectralRecipe::Init(sr, hopSize, bufferDepth);
        rand_.Init(11111u);
        clock_.Init(sr);
        clock_.SetBpm(120.0f);
        clock_.SetSubdivisionFromIntensity(params_.intensity);
        holdNorm_ = 0.0f;
        advancePerHop_ = 1.0f / static_cast<float>(bufferDepth);
    }

    void SpectralStutterRecipe::SetBpm(float bpm)
    {
        clock_.SetBpm(bpm);
    }

    void SpectralStutterRecipe::UpdateParamsFromEnergy()
    {
        pitchProb_ = params_.energy;
    }

    void SpectralStutterRecipe::UpdateParamsFromIntensity()
    {
        clock_.SetSubdivisionFromIntensity(params_.intensity);
    }

    void SpectralStutterRecipe::OnHop()
    {
        if (clock_.TickBy(hopSize_))
        {
            holdNorm_ = rand_.GetFloat() * 0.4f;  

            if (rand_.GetFloat() < pitchProb_)
            {
                float e = params_.energy;
                int poolSize = 5 + static_cast<int>(e * 2.5f);
                poolSize = utils::Clamp(poolSize, 5, 7);
                size_t idx = static_cast<size_t>(rand_.GetFloat() * poolSize);
                if (idx >= static_cast<size_t>(poolSize)) idx = poolSize - 1;
                params_.pitchSt = kPitchPool_[idx];
            }
            else
            {
                params_.pitchSt = 0.0f;
            }
        }
        else
        {
            holdNorm_ += advancePerHop_;
            holdNorm_ = utils::Clampf(holdNorm_, 0.0f, 1.0f);
        }

        params_.setUnifiedLookback(holdNorm_);
    }
}
