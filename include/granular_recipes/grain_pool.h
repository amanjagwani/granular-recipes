#pragma once
#include <cstddef>
#include <cstdint>
#include "granular_recipes/grain.h"

namespace gr
{
    class GrainPool
    {
    public:
        GrainPool() = default;
        ~GrainPool() = default;

        void Init(Grain *grains, size_t maxGrains);

        void Reset();

        Grain *TrySpawn();
        void Release(Grain *g);

        Grain *GetGrains() { return grains_; }
        size_t GetMaxGrains() const { return maxGrains_; }

        size_t ActiveCount() const
        {
            return activeCount_;
        }
    private:
        Grain *grains_{nullptr};
        size_t maxGrains_{0};
        size_t activeCount_{0};
        Grain* freePtr_{nullptr};
        GrainPool(const GrainPool &) = delete;
        GrainPool &operator=(const GrainPool &) = delete;
    };
}
