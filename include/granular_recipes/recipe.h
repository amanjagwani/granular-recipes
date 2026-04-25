#pragma once
#include <cstdint>
#include <cstddef>
#include "granular_recipes/granular_params.h"
#include "granular_recipes/core/subdivision_clock.h"

namespace gr
{

    class Recipe
    {
    public:
        Recipe() = default;
        virtual ~Recipe() = default;

        virtual void Init(float sr, size_t bufSize) { sampleRate_ = sr; bufSize_ = bufSize; }
        virtual void OnSample() = 0;
        virtual void OnSpawn() = 0;
        virtual void UpdateParamsFromEnergy() = 0;
        virtual void UpdateParamsFromIntensity() {}

        void SetEnergy(float energy) { params_.energy = energy; }
        void SetIntensity(float intensity) { params_.intensity = intensity; }
        void SetJitter(float jitter) { params_.jitter = jitter; }
        void SetSpread(float spread) { params_.spread = spread; }

        GranularParams *GetParams() { return &params_; }

    protected:
        GranularParams params_{};
        float sampleRate_{48000.0f};
        size_t bufSize_{0};
    };
}


