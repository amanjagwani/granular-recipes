#pragma once
#include <cstdint>
#include "granular_recipes/recipe.h"
#include "granular_recipes/core/random.h"
#include "granular_recipes/core/subdivision_clock.h"

namespace gr
{
    class StutterRecipe : public Recipe
    {
    public:
        StutterRecipe() = default;

        void Init(float sr, size_t bufSize) override;
        void OnSpawn() override;
        void OnSample() override;
        void UpdateParamsFromEnergy() override;
        void UpdateParamsFromIntensity() override;

        void SetBpm(float bpm);

    private:
        const float pitches_[5] = {-12, -7, 0, 7, 12};

        core::Random rand_;
        core::SubdivisionClock clock_;

        float bpm_{120.0f};

        float holdOffsetSamps_{1000.0f};

        float baseGrainSizeS_{0.10f};
        float baseDensityHz_{10.0f};

        float currentPitchSt_{0.0f};
        float currentGrainSizeS_{0.10f};
        float currentDensityHz_{10.0f};
        bool currentReverse_{false};
    };
}
