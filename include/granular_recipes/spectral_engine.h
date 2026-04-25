#pragma once
#include <cstddef>
#include <cstdint>
#include "granular_recipes/spectral_recipe.h"
#include "granular_recipes/spsc_queue.h"

namespace gr
{
    enum class SpectralMacro : uint8_t
    {
        ENERGY,
        INTENSITY
    };

    struct SpectralHopOutput
    {
        uint16_t readPositionLo;
        uint16_t readPositionMid;
        uint16_t readPositionHi;
        uint16_t blurFrames;
        float invBlur;
        float pitchRatio;
    };

    class SpectralEngine
    {
    public:
        SpectralEngine() = default;
        ~SpectralEngine() = default;

        void Init(float sr, uint32_t hopSize, uint32_t bufferDepth,
                  SpectralRecipe **recipes, size_t numRecipes);

        void SetRecipe(size_t index);
        void SetMacro(SpectralMacro macro, float val);

        size_t GetRecipeIndex() const { return recipeIdx_; }
        size_t GetNumRecipes() const { return numRecipes_; }

        void OnHop(uint32_t writePtr);

        void Process();

        SpectralHopOutput GetOutput() const;

    private:
        SpectralEngine(const SpectralEngine &) = delete;
        SpectralEngine &operator=(const SpectralEngine &) = delete;

        struct MacroEvent
        {
            SpectralMacro macro;
            float value;
        };
        SpscQueue<MacroEvent, 32> macroQ_;

        struct RecipeEvent
        {
            size_t index;
        };
        SpscQueue<RecipeEvent, 8> recipeQ_;

        void ApplyMacroEvent_(SpectralMacro macro, float val);
        void ApplyRecipeEvent_(size_t index);

        float sampleRate_{48000.0f};
        uint32_t hopSize_{256};
        uint32_t bufferDepth_{32};

        SpectralRecipe *recipe_{nullptr};
        SpectralRecipe **recipes_{nullptr};
        size_t numRecipes_{0};
        size_t recipeIdx_{0};
        uint32_t lastWritePtr_{0};
    };
}
