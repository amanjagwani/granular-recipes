#pragma once
#include <cstdint>

namespace gr::core
{
    class Random
    {
    public:
        Random() = default;

        void Init(uint32_t seed = 12345u)
        {
            state_ = seed ? seed : 1u;
        }

        float GetFloat()
        {
            state_ ^= state_ << 13;
            state_ ^= state_ >> 17;
            state_ ^= state_ << 5;
            return static_cast<float>(state_) / 4294967296.0f;
        }

    private:
        uint32_t state_{12345u};
    };
} // namespace gr::core
