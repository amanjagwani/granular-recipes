#pragma once

namespace gr::core
{
    class DcBlock
    {
    public:
        DcBlock() = default;

        void Init(float sr)
        {
            r_ = 1.0f - (250.0f / sr);
            xPrev_ = 0.0f;
            yPrev_ = 0.0f;
        }

        float Process(float in)
        {
            float y = in - xPrev_ + r_ * yPrev_;
            xPrev_ = in;
            yPrev_ = y;
            return y;
        }

    private:
        float r_{0.995f};
        float xPrev_{0.0f};
        float yPrev_{0.0f};
    };
} // namespace gr::core
