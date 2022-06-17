#pragma once

namespace shared
{
    class Vector
    {
        float m_X;
        float m_Y;

    public:
        Vector(float, float);

        float X();
        float Y();

        float X(float);
        float Y(float);

        Vector &operator+(const Vector &) const;
        Vector &operator-(const Vector &) const;
        Vector &operator*(float) const;
        Vector &operator/(float) const;
        Vector &operator/=(float);
        Vector &operator*=(float);
        Vector &operator+=(const Vector &);
        Vector &operator-=(const Vector &);
        Vector &operator=(const Vector &);
    };
}
