#pragma once
#include <cstdint>
#include <cmath>
#include <cstddef>

namespace gr
{
    class CircularBufferStereo
    {

    public:
        enum class BufferChannel
        {
            LEFT,
            RIGHT
        };
        CircularBufferStereo() = default;
        ~CircularBufferStereo() = default;

        void Init(float *left, float *right, size_t size);
        size_t GetSize() const { return size_; }

        void Clear();
        void Write(float leftSamp, float rightSamp);

        float ReadHermite(BufferChannel channel, float offsetSamps) const;
        float ReadLinear(BufferChannel channel, float offsetSamps) const;
        inline size_t GetWriteIndex() const { return writeIdx_; }

    private:
        float *leftBuf_ = nullptr;
        float *rightBuf_ = nullptr;
        size_t size_ = 0;
        size_t mask_ = 0;
        size_t writeIdx_ = 0;

        float hermite(float y0, float y1, float y2, float y3, float t) const;
    };
}
