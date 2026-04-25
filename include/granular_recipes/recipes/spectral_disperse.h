#pragma once
#include "granular_recipes/spectral_recipe.h"
#include "granular_recipes/core/random.h"

namespace gr
{

    class SpectralDisperseRecipe : public SpectralRecipe
    {
    public:
        void Init(float sr, uint32_t hopSize, uint32_t bufferDepth) override;
        void UpdateParamsFromEnergy() override;
        void UpdateParamsFromIntensity() override;
        void OnSample() override;
        void OnHop() override;

    private:
        core::Random rand_;
        float holdNorm_{0.3f};
        float advancePerHop_{0.03125f};
        float spreadNorm_{0.0f};
        float walkLo_{0.0f};
        float walkMid_{0.0f};
        float walkHi_{0.0f};
    };
}
