#pragma once
#include <cstdint>
#include <cstddef>

namespace gr
{

enum class Subdivision : uint8_t
{
    WHOLE,
    HALF,
    QUARTER,
    EIGHTH,
    SIXTEENTH,
    THIRTYSECOND
};

namespace core
{

class SubdivisionClock
{
public:
    void Init(float sampleRate, float bpm = 120.0f)
    {
        sampleRate_ = sampleRate;
        bpm_ = bpm;
        div_ = Subdivision::QUARTER;
        updatePeriod();
        counter_ = 0;
    }

    void SetBpm(float bpm)
    {
        bpm_ = bpm;
        updatePeriod();
    }

    void SetSubdivision(Subdivision div)
    {
        if (div != div_)
        {
            div_ = div;
            updatePeriod();
            counter_ = 0;
        }
    }

    
    bool SetSubdivisionFromIntensity(float val)
    {
        const Subdivision newDiv = intensityToSubdivision(val);
        if (newDiv != div_)
        {
            div_ = newDiv;
            updatePeriod();
            counter_ = 0;
            return true;
        }
        return false;
    }

    bool Tick()
    {
        counter_++;
        if (counter_ >= periodSamps_)
        {
            counter_ = 0;
            return true;
        }
        return false;
    }

    bool TickBy(size_t samples)
    {
        counter_ += samples;
        if (counter_ >= periodSamps_)
        {
            counter_ = 0;
            return true;
        }
        return false;
    }

    void Reset() { counter_ = 0; }

    size_t GetPeriodSamps() const { return periodSamps_; }
    Subdivision GetSubdivision() const { return div_; }
    float GetBpm() const { return bpm_; }

private:
    float sampleRate_{48000.0f};
    float bpm_{120.0f};
    Subdivision div_{Subdivision::QUARTER};
    size_t periodSamps_{0};
    size_t counter_{0};

    void updatePeriod()
    {
        if (bpm_ <= 0.0f)
            return;
        const float beatPeriodS = 60.0f / bpm_;
        const float clockPeriodS = beatPeriodS / divMultiplier();
        periodSamps_ = static_cast<size_t>(clockPeriodS * sampleRate_);
        if (periodSamps_ < 1)
            periodSamps_ = 1;
    }

    float divMultiplier() const
    {
        switch (div_)
        {
        case Subdivision::WHOLE:
            return 0.25f;
        case Subdivision::HALF:
            return 0.5f;
        case Subdivision::QUARTER:
            return 1.0f;
        case Subdivision::EIGHTH:
            return 2.0f;
        case Subdivision::SIXTEENTH:
            return 4.0f;
        case Subdivision::THIRTYSECOND:
            return 8.0f;
        default:
            return 1.0f;
        }
    }

    static Subdivision intensityToSubdivision(float intensity)
    {
        if (intensity < 0.16f)
            return Subdivision::WHOLE;
        else if (intensity < 0.32f)
            return Subdivision::HALF;
        else if (intensity < 0.48f)
            return Subdivision::QUARTER;
        else if (intensity < 0.64f)
            return Subdivision::EIGHTH;
        else if (intensity < 0.80f)
            return Subdivision::SIXTEENTH;
        else
            return Subdivision::THIRTYSECOND;
    }
};

} // namespace core
} // namespace gr
