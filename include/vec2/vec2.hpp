#pragma once

#include <string>
#include <iostream>
#include <concepts>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

namespace math
{
    template<arithmetic T>
    class Vec2
    {
    public:
        T x, y;

    public:
        Vec2() : x(0), y(0)
        {}

        // Vec2(float v) : x(v), y(v)
        // {}

        Vec2(T x, T y) : x(x), y(y)
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

        const Vec2& set(T x, T y);
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

        friend Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs)
        {
            return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        friend Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs)
        {
            return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
        }
        
        friend std::ostream& operator<<(std::ostream& out, const Vec2<T>& o)
        {
            out << '(' << o.x << ',' << o.y << ')';
            return out;
        }
        
        operator std::string() const
        {
            return '(' + std::to_string(this->x) + ',' + std::to_string(this->y) + ')';
        }
    };
}