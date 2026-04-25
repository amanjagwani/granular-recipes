#pragma once
#include <cstdint>
#include "granular_recipes/recipe.h"
#include "granular_recipes/core/random.h"
#include "granular_recipes/core/phasor.h"
#include <array>

namespace gr
{
    class CloudRecipe : public Recipe
    {
    public:
        CloudRecipe() = default;

        void Init(float sr, size_t bufSize) override;
        void OnSpawn() override;
        void OnSample() override;
        void UpdateParamsFromEnergy() override;
        void UpdateParamsFromIntensity() override;

    private:
        core::Phasor phasor_;
        core::Random rand_;
        float scanRate_{0.10f};
        float scanDepth_{0.50f};
    };
}
