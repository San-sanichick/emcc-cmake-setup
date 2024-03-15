#pragma once

#include <string>
#include <iostream>


namespace math
{
    class Vec2
    {
    public:
        float x, y;

    public:
        Vec2() : x(0), y(0)
        {}

        // Vec2(float v) : x(v), y(v)
        // {}

        Vec2(float x, float y) : x(x), y(y)
        {}

        Vec2(const Vec2& o) : x(o.x), y(o.y)
        {}

        Vec2(Vec2&& o) noexcept : x(o.x), y(o.y) 
        {
            o.x = 0;
            o.y = 0;
        }

        ~Vec2()
        {}

        const Vec2& set(float x, float y);
        // const Vec2& set(const Vec2 &o);

        inline Vec2& operator+=(const Vec2& rhs)
        {
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }

        inline Vec2& operator-=(const Vec2 &rhs)
        {
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }

        friend Vec2 operator+(Vec2 lhs, const Vec2& rhs);
        friend Vec2 operator-(Vec2 lhs, const Vec2& rhs);

        const std::string toString();
    };
}