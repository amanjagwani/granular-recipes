#pragma once
#include <cstddef>
#include <cstdint>
#include <cmath>
#include "granular_recipes/granular_processor.h"
#include "granular_recipes/recipe.h"
#include "granular_recipes/fourPole.h"
#include "granular_recipes/spsc_queue.h"

namespace gr
{
    enum class Macro : uint8_t
    {
        ENERGY,
        INTENSITY,
        CUTOFF,
        RESONANCE,
        GRANMIX,
        MIX
    };

    class Engine
    {

    public:
        Engine() = default;
        ~Engine() = default;

        void Init(float sr, float *bufL, float *bufR, size_t bufSize,
                  Grain *grainBuf, size_t maxGrains, float *windowBuf, size_t windowSize,
                  Recipe **recipes, size_t numRecipes);
        void SetRecipe(size_t index);
        size_t GetRecipeIndex() const { return recipeIdx_; }
        size_t GetNumRecipes() const { return numRecipes_; }

        void SetMacro(gr::Macro macro, float val);

        void OnBlock(size_t blockSize);
        void Process(float inL, float inR, float &outL, float &outR);

    private:
        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

        struct MacroEvent
        {
            Macro macro;
            float value;
        };
        SpscQueue<MacroEvent, 32> macroQ_;

        struct RecipeEvent
        {
            size_t index;
        };
        SpscQueue<RecipeEvent, 8> recipeQ_;

        void ApplyMacroEvent_(Macro macro, float val);
        void ApplyRecipeEvent_(size_t index);

        float sampleRate_{48000.0f};
        size_t bufSize_{0};
        GranularProcessor granular_;
        Recipe *recipe_{nullptr};
        Recipe **recipes_{nullptr};
        size_t numRecipes_{0};
        size_t recipeIdx_{0};

        FourPole lpfL_, lpfR_;

        float cutoff_{20000.f};
        float res_{0.1f};
        float mix_{0.9f};
        float granMix_{1.0f};

        float mixDryGain_{0.0f}, mixWetGain_{1.0f};
    };
} // namespace gr
