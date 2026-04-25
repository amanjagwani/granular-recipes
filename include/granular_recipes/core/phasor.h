#pragma once

namespace gr::core
{
    class Phasor
    {
    public:
        Phasor() = default;

        void Init(float sr)
        {
            sampleRate_ = sr;
            phase_ = 0.0f;
            inc_ = 0.0f;
        }

        void SetFreq(float hz)
        {
            inc_ = hz / sampleRate_;
        }

        float Process()
        {
            float out = phase_;
            phase_ += inc_;
            if (phase_ >= 1.0f)
                phase_ -= 1.0f;
            if (phase_ < 0.0f)
                phase_ += 1.0f;
            return out;
        }

    private:
        float sampleRate_{48000.0f};
        float phase_{0.0f};
        float inc_{0.0f};
    };
} // namespace gr::core
