#include "granular_recipes/granular_processor.h"
#include <cmath>
#include "granular_recipes/utils.h"
#include "granular_recipes/recipe.h"

namespace gr
{
    void GranularProcessor::Init(float sr, float *bufL, float *bufR, size_t bufSize,
                                  Grain *grainBuf, size_t maxGrains, float *windowBuf, size_t windowSize)
    {
        sampleRate_ = sr;
        bufSize_ = bufSize;
        buf_.Init(bufL, bufR, bufSize);
        grainPool_.Init(grainBuf, maxGrains);
        window_.Init(windowBuf, windowSize);
        rand_.Init();
        dcBlockL_.Init(sr);
        dcBlockR_.Init(sr);
        fbPrevL_ = 0.f;
        fbPrevR_ = 0.f;
        spawnAccum_ = 0.f;
    }

    void GranularProcessor::SetRecipe(Recipe *recipe)
    {

        grainPool_.Reset();
        spawnAccum_ = 0.f;
        fbPrevL_ = 0.f;
        fbPrevR_ = 0.f;
        recipe_.store(recipe, std::memory_order_release);
        const GranularParams *p = recipe != nullptr ? recipe->GetParams() : nullptr;
        params_.store(p, std::memory_order_release);
    }

    void GranularProcessor::spawnGrain()
    {
        const GranularParams *p = params_.load(std::memory_order_acquire);
        Recipe *r = recipe_.load(std::memory_order_acquire);
        if (p == nullptr)
            return;

        const float numberOfGrains = p->densityHz / sampleRate_;
        spawnAccum_ += numberOfGrains;

        while (spawnAccum_ >= 1.0f)
        {
            spawnAccum_ -= 1.0f;

            if (p->densityJitter > 0.0f)
            {
                const float densityJitVal = (2.0f * rand_.GetFloat() - 1.0f) * p->densityJitter;
                spawnAccum_ += densityJitVal;
            }

            Grain *g = grainPool_.TrySpawn();
            if (g == nullptr)
            {
                break;
            }

            if (r != nullptr)
            {
                r->OnSpawn();
            }

            const float rate = utils::SemitonesToRate(p->pitchSt);
            const float rateWithReverse = p->reverse ? -rate : rate;
            g->rate = rateWithReverse;

            const float grainSizeSamps = p->grainSizeS * sampleRate_;
            const float grainInc = 1.0f - rateWithReverse;
            const float grainBufSpanSamps = grainSizeSamps * grainInc;

            float minLookback = kLookbackSafetySamps + std::abs(grainBufSpanSamps);
            float maxLookback = bufSize_ - 1 - kLookbackSafetySamps - std::abs(grainBufSpanSamps);

            const float randVal = 2.0f * rand_.GetFloat() - 1.0f;
            const float jitSpan = p->jitterRange * bufSize_ * p->jitter;
            float lookback = p->lookback * (bufSize_ - 1) + (randVal * jitSpan);

            if (lookback < minLookback)
                lookback = minLookback;
            else if (lookback > maxLookback)
                lookback = maxLookback;

            g->bufOffsetSamps = lookback;

            g->envPhase = 0.f;
            g->envInc = (grainSizeSamps > 1e-6f) ? (1.f / grainSizeSamps) : 1.f;

            const float randPan = (rand_.GetFloat() * 2.f - 1.f) * p->spread;
            g->pan = utils::Clampf(0.5f + 0.5f * randPan, 0.f, 1.f);
        }
    }

    void GranularProcessor::Process(float inL, float inR, float &outL, float &outR)
    {
        const GranularParams *p = params_.load(std::memory_order_acquire);
        Recipe *r = recipe_.load(std::memory_order_acquire);
        if (p == nullptr)
        {
            outL = inL;
            outR = inR;
            return;
        }
        const float inFbL = inL + (p->feedback * fbPrevL_);
        const float inFbR = inR + (p->feedback * fbPrevR_);

        if (!p->freeze)
        {
            buf_.Write(inFbL, inFbR);
        }

        if (r != nullptr)
        {
            r->OnSample();
        }

        spawnGrain();

        outL = 0.f;
        outR = 0.f;

        const float overlap = p->densityHz * p->grainSizeS;
        const float norm = overlap > 1.f ? (1.f / std::sqrt(overlap)) : 1.f;

        Grain *grains = grainPool_.GetGrains();
        const size_t maxGrains = grainPool_.GetMaxGrains();
        for (size_t i = 0; i < maxGrains; ++i)
        {
            Grain &g = grains[i];

            if (!g.active)
                continue;

            if (g.IsFinished())
            {
                grainPool_.Release(&g);
                continue;
            }

            const float env = window_.GetSample(g.envPhase);

            const float sampL = buf_.ReadHermite(CircularBufferStereo::BufferChannel::LEFT, g.bufOffsetSamps);
            const float sampR = buf_.ReadHermite(CircularBufferStereo::BufferChannel::RIGHT, g.bufOffsetSamps);

            outL += sampL * g.pan * env * p->gain * norm;
            outR += sampR * (1.f - g.pan) * env * p->gain * norm;

            g.Advance();

            if (g.bufOffsetSamps < 0.0f)
                g.bufOffsetSamps += static_cast<float>(bufSize_);
            else if (g.bufOffsetSamps >= static_cast<float>(bufSize_))
                g.bufOffsetSamps -= static_cast<float>(bufSize_);
        }

        outL = utils::SoftClip(outL);
        outR = utils::SoftClip(outR);

        fbPrevL_ = dcBlockL_.Process(outL);
        fbPrevR_ = dcBlockR_.Process(outR);
    }
}
