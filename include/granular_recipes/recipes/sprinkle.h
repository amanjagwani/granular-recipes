#pragma once
#include <cstdint>
#include "granular_recipes/recipe.h"
#include "granular_recipes/core/random.h"
#include "granular_recipes/core/phasor.h"

namespace gr
{
    class SprinkleRecipe : public Recipe
    {
    public:
        SprinkleRecipe() = default;

        void Init(float sr, size_t bufSize) override;
        void OnSpawn() override;
        void OnSample() override;
        void UpdateParamsFromEnergy() override;
        void UpdateParamsFromIntensity() override;

    private:
        const float pitches_[5] = {-12, -7, 0, 7, 12};

        core::Random rand_;
        core::Phasor phasor_;

        float lastPhase_{0.0f};
        float holdRateHz_{1.0f};
        float posDepth_{0.02f};
        float posCenter_{0.02f};
        float reverseProb_{0.05f};
        float pitchShiftProb_{0.0f};
    };
}
