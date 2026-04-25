#include "granular_recipes/engine.h"
#include "granular_recipes/utils.h"

namespace gr
{
    void Engine::Init(float sr, float *bufL, float *bufR, size_t bufSize,
                      Grain *grainBuf, size_t maxGrains, float *windowBuf, size_t windowSize,
                      Recipe **recipes, size_t numRecipes)
    {
        sampleRate_ = sr;
        bufSize_ = bufSize;
        granular_.Init(sampleRate_, bufL, bufR, bufSize, grainBuf, maxGrains, windowBuf, windowSize);

        recipes_ = recipes;
        numRecipes_ = numRecipes;
        recipeIdx_ = 0;
        recipe_ = recipes_[0];

        if (recipe_ != nullptr)
        {
            recipe_->Init(sampleRate_, bufSize_);
            recipe_->UpdateParamsFromEnergy();
            recipe_->UpdateParamsFromIntensity();
            granular_.SetRecipe(recipe_);
        }

        lpfL_.Init(sampleRate_);
        lpfR_.Init(sampleRate_);
        lpfL_.SetFreq(20000.f);
        lpfR_.SetFreq(20000.f);
        lpfL_.SetRes(0.0f);
        lpfR_.SetRes(0.0f);
    }

    void Engine::SetRecipe(size_t index)
    {
        recipeQ_.push({index});
    }

    void Engine::ApplyRecipeEvent_(size_t index)
    {
        if (index >= numRecipes_)
            return;

        recipeIdx_ = index;
        recipe_ = recipes_[index];

        if (recipe_ != nullptr)
        {
            recipe_->Init(sampleRate_, bufSize_);
            recipe_->UpdateParamsFromEnergy();
            recipe_->UpdateParamsFromIntensity();
            granular_.SetRecipe(recipe_);
        }
    }

    void Engine::SetMacro(Macro macro, float val)
    {
        macroQ_.push({macro, val});
    }

    void Engine::ApplyMacroEvent_(Macro macro, float val)
    {
        switch (macro)
        {
        case Macro::ENERGY:
        {
            const float v = utils::Clampf(val, 0.0f, 1.0f);
            if (recipe_)
            {
                recipe_->SetEnergy(v);
                recipe_->UpdateParamsFromEnergy();
            }
        }
        break;

        case Macro::INTENSITY:
        {
            const float v = utils::Clampf(val, 0.0f, 1.0f);
            const float intensity = utils::Map01Linear(v, 0.0f, 0.98f);
            if (recipe_)
            {
                recipe_->SetIntensity(intensity);
                recipe_->UpdateParamsFromIntensity();
            }
        }
        break;

        case Macro::CUTOFF:
        {
            const float v = utils::Clampf(val, 0.0f, 1.0f);
            cutoff_ = utils::Map01ExpRate(v, 20.0f, 20000.0f);
            lpfL_.SetFreq(cutoff_);
            lpfR_.SetFreq(cutoff_);
        }
        break;

        case Macro::RESONANCE:
        {
            const float v = utils::Clampf(val, 0.0f, 1.0f);
            res_ = utils::Map01Linear(v, 0.0f, 0.95f);
            lpfL_.SetRes(res_);
            lpfR_.SetRes(res_);
        }
        break;

        case Macro::GRANMIX:
        {
            const float v = utils::Clampf(val, 0.0f, 1.0f);
            granMix_ = utils::Map01Linear(v, 0.0f, 1.0f);
        }
        break;

        case Macro::MIX:
        {
            const float v = utils::Clampf(val, 0.0f, 1.0f);
            mix_ = utils::Map01Linear(v, 0.0f, 1.0f);
        }
        break;
        }
    }

    void Engine::OnBlock(size_t blockSize)
    {
        RecipeEvent recipeEvent;
        size_t pendingIdx = recipeIdx_;
        bool hasRecipeEvent = false;

        while (recipeQ_.pop(recipeEvent))
        {
            pendingIdx = recipeEvent.index;
            hasRecipeEvent = true;
        }

        if (hasRecipeEvent && pendingIdx != recipeIdx_)
        {
            ApplyRecipeEvent_(pendingIdx);
        }

        MacroEvent macroEvent;
        while (macroQ_.pop(macroEvent))
        {
            ApplyMacroEvent_(macroEvent.macro, macroEvent.value);
        }

        utils::EqualPowerGains(mix_, mixDryGain_, mixWetGain_);
    }

    void Engine::Process(float inL, float inR, float &outL, float &outR)
    {
        float granL = 0.f, granR = 0.f;
        granular_.Process(inL, inR, granL, granR);

        const float filtL = lpfL_.Process(granL);
        const float filtR = lpfR_.Process(granR);

        outL = mixDryGain_ * inL + mixWetGain_ * filtL;
        outR = mixDryGain_ * inR + mixWetGain_ * filtR;
    }

}
