#pragma once
#include <cstdint>
#include "granular_recipes/utils.h"

namespace gr
{
    struct Grain
    {
        bool active{false};
        float bufOffsetSamps{0.f};
        float rate{0.0f};
        float envPhase{0.f};
        float envInc{0.f};
        float pan{0.f};
        float amp{0.f};

        Grain* nextFree{nullptr};

        inline void Advance()
        {
            bufOffsetSamps += (1.0f - rate);
            envPhase += envInc;
        }

        inline bool IsFinished() const
        {
            return envPhase >= 1.f;
        }
    };
} // namespace gr
