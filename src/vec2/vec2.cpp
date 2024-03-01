#include "vec2.h"

namespace math
{
    const float Vec2::X() const
    {
        return this->x;
    }

    const float Vec2::Y() const
    {
        return this->y;
    }

    const Vec2& Vec2::set(float x, float y)
    {
        this->x = x;
        this->y = y;

        return *this;
    }
    // const Vec2 &Vec2::set(const Vec2 &o)
    // {
    //     this->x = o.x;
    //     this->y = o.y;

    //     return *this;
    // }

    Vec2 &Vec2::operator+=(const Vec2 &rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    Vec2 operator+(Vec2 lhs, const Vec2 &rhs)
    {
        return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    Vec2 &Vec2::operator-=(const Vec2 &rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    Vec2 operator-(Vec2 lhs, const Vec2 &rhs)
    {
        return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }
}