#include "granular_recipes/spectral_engine.h"
#include "granular_recipes/utils.h"

namespace gr
{
    void SpectralEngine::Init(float sr, uint32_t hopSize, uint32_t bufferDepth,
                              SpectralRecipe **recipes, size_t numRecipes)
    {
        sampleRate_ = sr;
        hopSize_ = hopSize;
        bufferDepth_ = bufferDepth;

        recipes_ = recipes;
        numRecipes_ = numRecipes;
        recipeIdx_ = 0;
        recipe_ = recipes_[0];

        if (recipe_ != nullptr)
        {
            recipe_->Init(sampleRate_, hopSize_, bufferDepth_);
            recipe_->UpdateParamsFromEnergy();
            recipe_->UpdateParamsFromIntensity();
        }
    }

    void SpectralEngine::SetRecipe(size_t index)
    {
        recipeQ_.push({index});
    }

    void SpectralEngine::SetMacro(SpectralMacro macro, float val)
    {
        macroQ_.push({macro, val});
    }

    void SpectralEngine::ApplyRecipeEvent_(size_t index)
    {
        if (index >= numRecipes_)
            return;

        recipeIdx_ = index;
        recipe_ = recipes_[index];

        if (recipe_ != nullptr)
        {
            recipe_->Init(sampleRate_, hopSize_, bufferDepth_);
            recipe_->UpdateParamsFromEnergy();
            recipe_->UpdateParamsFromIntensity();
        }
    }

    void SpectralEngine::ApplyMacroEvent_(SpectralMacro macro, float val)
    {
        switch (macro)
        {
        case SpectralMacro::ENERGY:
        {
            const float v = utils::Clampf(val, 0.0f, 1.0f);
            if (recipe_)
            {
                recipe_->SetEnergy(v);
            }
        }
        break;

        case SpectralMacro::INTENSITY:
        {
            const float v = utils::Clampf(val, 0.0f, 1.0f);
            if (recipe_)
            {
                recipe_->SetIntensity(v);
            }
        }
        break;
        }
    }

    void SpectralEngine::OnHop(uint32_t writePtr)
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

        lastWritePtr_ = writePtr;

        if (recipe_)
        {
            recipe_->SetWritePtr(writePtr);
            recipe_->OnHop();
        }
    }

    void SpectralEngine::Process()
    {
        if (recipe_)
        {
            recipe_->OnSample();
        }
    }

    SpectralHopOutput SpectralEngine::GetOutput() const
    {
        SpectralHopOutput out{};
        if (!recipe_)
            return out;

        const SpectralParams *p = recipe_->GetParams();

        int32_t recent = (lastWritePtr_ == 0)
                             ? static_cast<int32_t>(bufferDepth_ - 1)
                             : static_cast<int32_t>(lastWritePtr_ - 1);

        auto lookbackToPos = [this, recent](float lbNorm) -> uint16_t
        {
            int32_t offset = static_cast<int32_t>(lbNorm * static_cast<float>(bufferDepth_ - 1));
            int32_t pos = recent - offset;
            while (pos < 0)
                pos += static_cast<int32_t>(bufferDepth_);
            return static_cast<uint16_t>(pos % bufferDepth_);
        };

        out.readPositionLo = lookbackToPos(p->lookbackLo);
        out.readPositionMid = lookbackToPos(p->lookbackMid);
        out.readPositionHi = lookbackToPos(p->lookbackHi);

        uint16_t blur = p->blurFrames;
        if (blur < 1)
            blur = 1;
        if (blur > static_cast<uint16_t>(bufferDepth_))
            blur = static_cast<uint16_t>(bufferDepth_);
        out.blurFrames = blur;
        out.invBlur = 1.0f / static_cast<float>(blur);

        out.pitchRatio = p->pitchRatio();

        return out;
    }
}
