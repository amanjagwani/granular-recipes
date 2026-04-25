#pragma once
#include <cstdint>
#include <cmath>
#include "granular_recipes/config.h"

namespace gr::utils
{
    constexpr bool IsPowerOfTwo(uint32_t x) noexcept
    {
        return (x != 0) && ((x & (x - 1)) == 0);
    }

    inline size_t Wrap(size_t idx, size_t mask, size_t size) noexcept
    {
        return (mask != 0) ? (idx & mask) : (idx % size);
    }

    inline float WrapF(float idx, const size_t size) noexcept
    {
        const float sizeF = static_cast<float>(size);
        float wrappedIdx = idx;
        while (wrappedIdx < 0.f)
            wrappedIdx += sizeF;
        while (wrappedIdx >= sizeF)
            wrappedIdx -= sizeF;
        return wrappedIdx;
    }

    constexpr float Clampf(float val, float min, float max) noexcept
    {
        return (val < min) ? min : (val > max) ? max
                                               : val;
    }

    constexpr int Clamp(int val, int min, int max) noexcept
    {
        return (val < min) ? min : (val > max) ? max
                                               : val;
    }

    inline float SemitonesToRate(float st) noexcept
    {
        return std::pow(2.0f, st / 12.0f);
    }

    inline float SoftClip(float x) noexcept
    {
        float drive = 1.0f;
        return std::tanh(drive * x);
    }

    inline float MapLin(float val, float inMin, float inMax, float outMin, float outMax, bool saturate = true) noexcept
    {
        if (saturate)
        {
            val = Clampf(val, inMin, inMax);
        }
        const float denom = (inMax - inMin);
        if (denom == 0.0f)
            return outMin;
        const float t = (val - inMin) / denom;
        return outMin + t * (outMax - outMin);
    }

    inline float Map01Linear(float v01, float outMin, float outMax, bool saturate = true) noexcept
    {
        if (saturate)
        {
            v01 = Clampf(v01, 0.0f, 1.0f);
        }
        return outMin + v01 * (outMax - outMin);
    }

    inline float Map01ExpRate(float v01, float outMin, float outMax, bool saturate = true) noexcept
    {
        if (saturate)
        {
            v01 = Clampf(v01, 0.0f, 1.0f);
        }
        if (outMin <= 0.0f)
            return outMin;
        const float ratio = outMax / outMin;
        return outMin * std::pow(ratio, v01);
    }

    inline float Map01Pow(float v01, float exponent, bool saturate = true) noexcept
    {
        if (saturate)
        {
            v01 = Clampf(v01, 0.0f, 1.0f);
        }
        return std::pow(v01, exponent);
    }

    inline void EqualPowerGains(float mix, float &dryG, float &wetG) noexcept
    {
        float clampedMix = Clampf(mix, 0.0f, 1.0f);
        dryG = std::cos(0.5f * gr::cfg::kPi * clampedMix);
        wetG = std::sin(0.5f * gr::cfg::kPi * clampedMix);
    }

}
