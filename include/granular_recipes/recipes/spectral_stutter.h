#pragma once
#include "granular_recipes/spectral_recipe.h"
#include "granular_recipes/core/random.h"
#include "granular_recipes/core/subdivision_clock.h"

namespace gr
{
    
    class SpectralStutterRecipe : public SpectralRecipe
    {
    public:
        void Init(float sr, uint32_t hopSize, uint32_t bufferDepth) override;
        void SetBpm(float bpm);
        void UpdateParamsFromEnergy() override;
        void UpdateParamsFromIntensity() override;
        void OnHop() override;

    private:
        static constexpr float kPitchPool_[7] = {-12.0f, -7.0f, 0.0f, 5.0f, 7.0f, 12.0f, 19.0f};

        core::Random rand_;
        core::SubdivisionClock clock_;
        float holdNorm_{0.0f};
        float advancePerHop_{0.03125f};
        float pitchProb_{0.0f};
    };
}
