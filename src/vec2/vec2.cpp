#include "vec2/vec2.hpp"
// #include <format>

namespace math
{
    template<arithmetic T>
    const Vec2<T>& Vec2<T>::set(T x, T y)
    {
        this->x = x;
        this->y = y;

        return *this;
    }

    template <arithmetic T>
    const Vec2<T> &Vec2<T>::set(const Vec2<T> &o)
    {
        this->x = o.x;
        this->y = o.y;
    }
}