#pragma once
#include <cstdint>
#include <cmath>
#include "granular_recipes/grain.h"
#include "granular_recipes/grain_pool.h"
#include "granular_recipes/window_lut.h"
#include "granular_recipes/circular_buffer_stereo.h"
#include "granular_recipes/granular_params.h"
#include "granular_recipes/core/random.h"
#include "granular_recipes/core/dc_block.h"
#include <atomic>

namespace gr
{
    class Recipe;

    class GranularProcessor
    {
    public:
        GranularProcessor() = default;
        ~GranularProcessor() = default;

        void Init(float sr, float *bufL, float *bufR, size_t bufSize,
                  Grain *grainBuf, size_t maxGrains, float *windowBuf, size_t windowSize);
        void Process(float inL, float inR, float &outL, float &outR);

        void SetRecipe(Recipe *recipe);

    private:
        CircularBufferStereo buf_;
        GrainPool grainPool_;
        WindowLUT window_;
        std::atomic<const GranularParams *> params_{nullptr};

        std::atomic<Recipe *> recipe_{nullptr};

        float fbPrevL_, fbPrevR_;
        float sampleRate_;
        float spawnAccum_;

        static constexpr float kLookbackSafetySamps = 64.0f;

        core::Random rand_;
        core::DcBlock dcBlockL_, dcBlockR_;

        size_t bufSize_{0};

        void spawnGrain();
    };
}
