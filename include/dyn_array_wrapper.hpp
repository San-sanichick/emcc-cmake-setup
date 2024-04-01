/**
 * @brief A non-owning read-only wrapper around a C-style dynamic array
 * 
 * @tparam T array element type
 */
template<typename T>
class DynArrayWrapper
{
private:
    const T* buf;
    const size_t bufSize;

public:
    DynArrayWrapper(const T* ptr, const size_t size)
        : buf(ptr), bufSize(size)
    {}

    const inline constexpr T& operator[](size_t index) const
    {
        return this->data[index];
    }

    const inline constexpr T* data() const
    {
        return this->buf;
    }
    
    const inline constexpr size_t size() const
    {
        return this->bufSize;
    }
};