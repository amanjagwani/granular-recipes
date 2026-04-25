#pragma once
#include <cstdint>
#include "granular_recipes/recipe.h"
#include "granular_recipes/core/random.h"
#include "granular_recipes/core/phasor.h"

namespace gr
{
    class LushRecipe : public Recipe
    {
    public:
        LushRecipe() = default;

        void Init(float sr, size_t bufSize) override;
        void OnSpawn() override;
        void OnSample() override;
        void UpdateParamsFromEnergy() override;
        void UpdateParamsFromIntensity() override;

    private:
        const float fifths_[2] = {-5, 7};
        const float fullStack_[6] = {-12, -5, 7, 12, 19, 24};

        core::Phasor phasor_;
        core::Random rand_;

        float scanRate_{0.10f};
        float scanDepth_{0.02f};
        float scanCenter_{0.005f};
        float pitchShiftProb_{0.0f};
        uint8_t pitchTier_{0}; // 0=none, 1=fifths, 2=full stack
    };
}
