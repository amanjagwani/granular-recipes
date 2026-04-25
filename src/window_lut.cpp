#include "granular_recipes/window_lut.h"
#include <cmath>
#include "granular_recipes/config.h"

namespace gr
{
    void WindowLUT::Init(float *lut, size_t windowSize)
    {
        lut_ = lut;
        windowSize_ = windowSize;

        for (size_t i = 0; i < windowSize_; ++i)
        {
            lut_[i] = 0.5f * (1.f - std::cos((2.f * cfg::kPi * i) / (windowSize_ - 1)));
        }
    }

    float WindowLUT::GetSample(float phase) const
    {
        if (phase <= 0.f)
            return 0.f;
        if (phase >= 1.f)
            return 0.f;

        const float idx = phase * static_cast<float>(windowSize_ - 1);
        const size_t idxInt = static_cast<size_t>(idx);
        const float frac = idx - static_cast<float>(idxInt);

        if (idxInt >= windowSize_ - 1)
            return lut_[windowSize_ - 1];

        return lut_[idxInt] + frac * (lut_[idxInt + 1] - lut_[idxInt]);
    }
}
