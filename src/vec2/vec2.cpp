#include "vec2/vec2.h"
#include <format>

namespace math
{
    const Vec2& Vec2::set(float x, float y)
    {
        this->x = x;
        this->y = y;

        return *this;
    }

    Vec2 operator+(Vec2 lhs, const Vec2& rhs)
    {
        return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    Vec2 operator-(Vec2 lhs, const Vec2& rhs)
    {
        return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    

    const std::string Vec2::toString()
    {
        return std::format("({}, {})", x, y);
    }
}