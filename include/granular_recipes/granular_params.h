#pragma once
#include <cstddef>
#include <cstdint>

namespace gr
{
    enum class WindowType : uint8_t
    {
        HANN
    };

    struct GranularParams
    {
        float energy{0.5f};
        float grainSizeS{0.1f};
        float densityHz{10.0f};
        float lookback{0.25f};     // how far back from the write head (0 = recent, 1 = full buffer)
        float pitchSt{0.0f};
        float jitter{0.0f};
        float jitterRange{0.0f};
        float densityJitter{0.0f};
        float spread{0.0f};
        float gain{0.5f};
        float feedback{0.0f};      // audio DSP recirculation coefficient
        float intensity{0.0f};     // Intensity macro value (0-1)
        bool freeze{false};
        bool reverse{false};

        WindowType windowType{WindowType::HANN};
    };
}
