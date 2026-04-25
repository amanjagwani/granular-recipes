#include "granular_recipes/circular_buffer_stereo.h"
#include <cstring>
#include <algorithm>
#include <cmath>
#include "granular_recipes/utils.h"

namespace gr
{
    void CircularBufferStereo::Init(float *left, float *right, size_t size)
    {
        leftBuf_ = left;
        rightBuf_ = right;
        size_ = size;
        mask_ = utils::IsPowerOfTwo(size_) ? size_ - 1u : 0u;
        writeIdx_ = 0;
        Clear();
    }

    void CircularBufferStereo::Clear()
    {
        if (leftBuf_ == nullptr || rightBuf_ == nullptr || size_ == 0)
            return;

        std::fill(leftBuf_, leftBuf_ + size_, 0.f);
        std::fill(rightBuf_, rightBuf_ + size_, 0.f);
        writeIdx_ = 0;
    }

    void CircularBufferStereo::Write(float leftSamp, float rightSamp)
    {
        if (leftBuf_ == nullptr || rightBuf_ == nullptr || size_ == 0)
            return;

        leftBuf_[writeIdx_] = leftSamp;
        rightBuf_[writeIdx_] = rightSamp;
        writeIdx_ = utils::Wrap(writeIdx_ + 1, mask_, size_);
    }

    float CircularBufferStereo::hermite(float y0, float y1, float y2, float y3, float t) const
    {
        float c0 = y1;
        float c1 = 0.5f * (y2 - y0);
        float c2 = y0 - (2.5f * y1) + (2.f * y2) - (0.5f * y3);
        float c3 = (0.5f * (y3 - y0)) + (1.5f * (y1 - y2));
        return ((c3 * t + c2) * t + c1) * t + c0;
    }

    float CircularBufferStereo::ReadHermite(BufferChannel channel, float offsetSamps) const
    {
        if (leftBuf_ == nullptr || rightBuf_ == nullptr || size_ == 0)
            return 0.0f;

        if (offsetSamps < 0.f)
            offsetSamps = 0.f;

        const float offFloor = std::floor(offsetSamps);
        const size_t offInt = static_cast<size_t>(offFloor);
        const float frac = offsetSamps - offFloor;

        const size_t idxBase = utils::Wrap(writeIdx_ - 1 - offInt, mask_, size_);
        const size_t idxM2 = utils::Wrap(idxBase - 2, mask_, size_);
        const size_t idxM1 = utils::Wrap(idxBase - 1, mask_, size_);
        const size_t idxP1 = utils::Wrap(idxBase + 1, mask_, size_);

        const float t = 1.0f - frac;

        const float *buf = (channel == BufferChannel::LEFT) ? leftBuf_ : rightBuf_;
        return hermite(buf[idxM2], buf[idxM1], buf[idxBase], buf[idxP1], t);
    }

    float CircularBufferStereo::ReadLinear(BufferChannel channel, float offsetSamps) const
    {
        if (leftBuf_ == nullptr || rightBuf_ == nullptr || size_ == 0)
            return 0.0f;

        if (offsetSamps < 0.f)
            offsetSamps = 0.f;

        const float offFloor = std::floor(offsetSamps);
        const size_t offInt = static_cast<size_t>(offFloor);
        const float frac = offsetSamps - offFloor;

        const size_t idxBase = utils::Wrap(writeIdx_ - 1 - offInt, mask_, size_);
        const size_t idxP1 = utils::Wrap(idxBase + 1, mask_, size_);

        const float *buf = (channel == BufferChannel::LEFT) ? leftBuf_ : rightBuf_;
        const float samp0 = buf[idxBase];
        const float samp1 = buf[idxP1];

        return samp0 * (1.0f - frac) + samp1 * frac;
    }
}
