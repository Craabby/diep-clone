#pragma once

namespace shared::physics
{
    class Vector
    {
    protected:
        float m_X = 0;
        float m_Y = 0;

    public:
        Vector(float, float);

        virtual float X() const;
        virtual float Y() const;

        virtual void X(float);
        virtual void Y(float);

        Vector operator+(const Vector &) const;
        Vector operator-(const Vector &) const;
        Vector operator*(float) const;
        Vector operator/(float) const;
        Vector &operator/=(float);
        Vector &operator*=(float);
        Vector &operator+=(const Vector &);
        Vector &operator-=(const Vector &);
    };
}
