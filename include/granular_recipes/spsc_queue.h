#pragma once
#include <atomic>
#include <cstddef>

namespace gr
{
    template <typename T, size_t N>
    class SpscQueue
    {
    public:
        bool push(const T &item)
        {
            const size_t writeIdx = writePtr_.load(std::memory_order_acquire);
            const size_t readIdx = readPtr_.load(std::memory_order_acquire);
            const size_t nextWriteIdx = (writeIdx + 1) % N;

            if (nextWriteIdx == readIdx)
            {
                return false;
            }

            buf_[writeIdx] = item;
            writePtr_.store(nextWriteIdx, std::memory_order_release);
            return true;
        }

        bool pop(T &item)
        {
            const size_t writeIdx = writePtr_.load(std::memory_order_acquire);
            const size_t readIdx = readPtr_.load(std::memory_order_acquire);

            if (readIdx == writeIdx)
            {
                return false;
            }
            item = buf_[readIdx];
            readPtr_.store((readIdx + 1) % N, std::memory_order_release);
            return true;
        }

    private:
        T buf_[N];
        std::atomic<size_t> readPtr_{0};
        std::atomic<size_t> writePtr_{0};
    };
} // namespace gr
