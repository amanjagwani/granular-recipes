#pragma once
#include <cstdint>
#include <cmath>

namespace gr
{
    struct SpectralParams
    {
        float energy{0.5f};
        float intensity{0.0f};
        float lookbackLo{0.0f};
        float lookbackMid{0.0f};
        float lookbackHi{0.0f};
        uint16_t blurFrames{1};
        float pitchSt{0.0f};        
        float rate{0.0f};           
        float jitter{0.0f};         
        float jitterRange{0.0f};    
        uint32_t writePtr{0};
        uint32_t bufferDepth{32};
        float pitchRatio() const
        {
            return std::pow(2.0f, pitchSt / 12.0f);
        }
        void setUnifiedLookback(float lb)
        {
            lookbackLo = lb;
            lookbackMid = lb;
            lookbackHi = lb;
        }
    };
}
