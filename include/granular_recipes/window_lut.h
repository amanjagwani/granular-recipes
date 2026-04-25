#pragma once
#include <cstddef>

namespace gr
{
    class WindowLUT
    {
    public:
        WindowLUT() = default;
        ~WindowLUT() = default;

        void Init(float *lut, size_t windowSize);
        float GetSample(float phase) const;

    private:
        float *lut_{nullptr};
        size_t windowSize_{0};
    };
}
