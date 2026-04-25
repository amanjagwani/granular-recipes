#include "granular_recipes/grain_pool.h"

namespace gr
{
    void GrainPool::Init(Grain *grains, size_t maxGrains)
    {
        grains_ = grains;
        maxGrains_ = maxGrains;
        activeCount_ = 0;

        for (size_t i = 0; i < maxGrains_; ++i)
        {
            grains_[i] = Grain{};
            grains_[i].active = false;

            if (i < maxGrains_ - 1)
            {
                grains_[i].nextFree = &grains_[i + 1];
            }
            else
            {
                grains_[i].nextFree = nullptr;
            }
        }
        freePtr_ = &grains_[0];
    }

    void GrainPool::Reset()
    {
        activeCount_ = 0;
        for (size_t i = 0; i < maxGrains_; ++i)
        {
            grains_[i] = Grain{};
            grains_[i].active = false;
            grains_[i].nextFree = (i < maxGrains_ - 1) ? &grains_[i + 1] : nullptr;
        }
        freePtr_ = &grains_[0];
    }

    Grain *GrainPool::TrySpawn()
    {
        if (freePtr_ == nullptr)
        {
            return nullptr;
        }

        Grain* g = freePtr_;
        freePtr_ = g->nextFree;

        g->active = true;
        g->nextFree = nullptr;
        g->bufOffsetSamps = 0.f;
        g->envPhase = 0.f;
        g->rate = 0.0f;
        g->envInc = 0.f;
        g->pan = 0.f;

        ++activeCount_;
        return g;
    }

    void GrainPool::Release(Grain *g)
    {
        if (g == nullptr || !g->active)
        {
            return;
        }

        g->active = false;
        g->nextFree = freePtr_;
        freePtr_ = g;
        --activeCount_;
    }
}
