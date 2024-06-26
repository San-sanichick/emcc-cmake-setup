#pragma once

#include "debug.hpp"


namespace utils
{
    /**
     * @brief A non-owning read-only wrapper around a C-style dynamic array
     * 
     * @tparam T array element type
     */
    template<typename T>
    class WeakReadonlyDynArrayWrapper
    {
    private:
        T* buf;
        size_t bufSize;

    public:
        WeakReadonlyDynArrayWrapper(T* ptr, size_t size)
            : buf(ptr), bufSize(size)
        {}

        WeakReadonlyDynArrayWrapper(const WeakReadonlyDynArrayWrapper& o) = delete;

        WeakReadonlyDynArrayWrapper(WeakReadonlyDynArrayWrapper&& o) noexcept
            : buf(std::exchange(o.buf, nullptr)), bufSize(std::exchange(o.bufSize, 0))
        {}

        const inline constexpr T& operator[](size_t index) const
        {
            CORE_ASSERT(index < this->bufSize, "index out of bounds");
            return this->data[index];
        }
        
        T& operator=(const T& o) = delete;
        
        const inline constexpr T& operator=(T&& o) const
        {
            this->buf = std::exchange(o.buf, nullptr);
            this->bufSize = std::exchange(o.bufSize, 0);
            return *this;
        }
        
        

        inline constexpr T* begin()
        {
            return this->buf;
        }

        inline constexpr T* end()
        {
            return this->buf + this->bufSize;
        }

        inline constexpr T* data() const
        {
            return this->buf;
        }
        
        inline constexpr size_t size() const
        {
            return this->bufSize;
        }
    };


    /**
     * @brief An owning read-only wrapper around a C-style dynamic array
     * 
     * @tparam T array element type
     */
    template<typename T>
    class ReadonlyDynArrayWrapper
    {
    private:
        T* buf;
        size_t bufSize;

    public:
        ReadonlyDynArrayWrapper(T* ptr, size_t size)
            : buf(ptr), bufSize(size)
        {}
        
        ReadonlyDynArrayWrapper(const ReadonlyDynArrayWrapper& o) = delete;
        
        ReadonlyDynArrayWrapper(ReadonlyDynArrayWrapper&& o) noexcept
            :buf(std::exchange(o.buf, nullptr)), bufSize(std::exchange(o.bufSize, 0))
        {}
        
        ~ReadonlyDynArrayWrapper()
        {
            delete[] this->buf;
        }

        const inline constexpr T& operator[](size_t index) const
        {
            CORE_ASSERT(index < this->bufSize, "index out of bounds");
            return this->data[index];
        }
        
        T& operator=(const T& o) = delete;

        const inline constexpr T& operator=(T&& o) const
        {
            this->buf = std::exchange(o.buf, nullptr);
            this->bufSize = std::exchange(o.bufSize, 0);
            return *this;
        }



        inline constexpr T* begin()
        {
            return this->buf;
        }

        inline constexpr T* end()
        {
            return this->buf + this->bufSize;
        }

        inline constexpr T* data() const
        {
            return this->buf;
        }
        
        inline constexpr size_t size() const
        {
            return this->bufSize;
        }
    };
}
