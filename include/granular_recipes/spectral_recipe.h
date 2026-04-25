#pragma once
#include <cstdint>
#include "granular_recipes/spectral_params.h"

namespace gr
{
    class SpectralRecipe
    {
    public:
        SpectralRecipe() = default;
        virtual ~SpectralRecipe() = default;

        virtual void Init(float sr, uint32_t hopSize, uint32_t bufferDepth)
        {
            sampleRate_ = sr;
            hopSize_ = hopSize;
            params_.bufferDepth = bufferDepth;
        }

        virtual void OnHop() = 0;
        virtual void OnSample() {}             
        virtual void UpdateParamsFromEnergy() = 0;
        virtual void UpdateParamsFromIntensity() {}

        void SetEnergy(float e)
        {
            params_.energy = e;
            UpdateParamsFromEnergy();
        }

        void SetIntensity(float i)
        {
            params_.intensity = i;
            UpdateParamsFromIntensity();
        }

        void SetWritePtr(uint32_t wp) { params_.writePtr = wp; }

        SpectralParams *GetParams() { return &params_; }

    protected:
        SpectralParams params_{};
        float sampleRate_{48000.0f};
        uint32_t hopSize_{256};
    };
}
