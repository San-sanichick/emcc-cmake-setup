#pragma once

#include <string>
#include <format>
#include <iostream>
#include <concepts>



template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

/// @brief Namespace for mathematical constructs
namespace math
{
    /// @brief 2D Vector class
    /// @tparam T type to be used internally
    template<arithmetic T>
    struct Vec2
    {
    public:
        T x, y;

    public:
        inline constexpr Vec2() : x(0), y(0)
        {}

        /// @brief 
        /// @param v 
        inline constexpr Vec2(T v) : x(v), y(v)
        {}

        /// @brief
        /// @param x
        /// @param y
        inline constexpr Vec2(T x, T y) : x(x), y(y)
        {}

        inline Vec2(std::initializer_list<T> l) : x(l.begin()[0]), y(l.begin()[1])
        {}

        /**
         * @brief
         * @param o
         * @
        */
        inline constexpr Vec2(const Vec2& o) : x(o.x), y(o.y)
        {}

        inline constexpr Vec2 (Vec2&& o) noexcept : x(o.x), y(o.y) 
        {
            o.x = 0;
            o.y = 0;
        }

        ~Vec2()
        {}



        inline const Vec2& set(T x, T y)
        {
            this->x = x;
            this->y = y;

            return *this;
        }

        inline const Vec2& set(const Vec2 &o)
        {
            this->x = o.x;
            this->y = o.y;
        }

        
        inline Vec2& operator=(const Vec2& rhs)
        {
            this->x = rhs.x;
            this->y = rhs.y;
            
            return *this;
        }
        
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

        inline friend Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs)
        {
            return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        inline friend Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs)
        {
            return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
        }
        
        inline constexpr auto operator<=>(const Vec2& rhs) const = default;

        
        inline friend std::ostream& operator<<(std::ostream& out, const Vec2<T>& o)
        {
            out << '(' << o.x << ',' << o.y << ')';
            return out;
        }
        
        inline operator std::string() const
        {
            return std::format("({}, {})", this->x, this->y);
        }
    };
}