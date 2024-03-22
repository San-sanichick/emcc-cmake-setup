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

    // template<arithmetic T>
    // Vec2<T> operator+(Vec2 lhs, const Vec2& rhs)
    // {
    //     return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    // }

    // Vec2 operator-(Vec2 lhs, const Vec2& rhs)
    // {
    //     return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    // }
    

    // template<arithmetic T>
    // const std::string Vec2<T>::toString()
    // {
    //     // return std::format("({}, {})", x, y);
    //     return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    // }
}