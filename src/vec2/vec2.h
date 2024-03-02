#pragma once


namespace math
{
    class Vec2
    {
    private:
        float x, y;

    public:
        Vec2() : x(0), y(0)
        {}

        // Vec2(float v) : x(v), y(v)
        // {}

        Vec2(float x, float y) : x(x), y(y)
        {}

        Vec2(const Vec2 &o) : x(o.x), y(o.y)
        {}

        const float X() const;
        const float Y() const;

        const Vec2& set(float x, float y);
        // const Vec2& set(const Vec2 &o);

        Vec2 &operator+=(const Vec2 &rhs);
        friend Vec2 operator+(Vec2 lhs, const Vec2 &rhs);

        Vec2 &operator-=(const Vec2 &rhs);
        friend Vec2 operator-(Vec2 lhs, const Vec2 &rhs);
    };
}