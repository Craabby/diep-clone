#include <Physics/Vector.hh>

namespace shared
{
    Vector::Vector(float x, float y)
        : m_X(x),
          m_Y(y)
    {
    }

    float Vector::X() const
    {
        return m_X;
    }

    float Vector::Y() const
    {
        return m_Y;
    }

    void Vector::X(float x)
    {
        m_X = x;
    }

    void Vector::Y(float y)
    {
        m_Y = y;
    }

    Vector Vector::operator+(const Vector &other) const
    {
        return Vector(X() + other.X(), Y() + other.Y());
    }

    Vector Vector::operator-(const Vector &other) const
    {
        return Vector(X() - other.X(), Y() - other.Y());
    }

    Vector Vector::operator*(float scale) const
    {
        return Vector(X() * scale, Y() * scale);
    }

    Vector Vector::operator/(float scale) const
    {
        return Vector(X() / scale, Y() / scale);
    }

    Vector &Vector::operator/=(float scale)
    {
        X(X() / scale);
        Y(Y() / scale);
        return *this;
    }

    Vector &Vector::operator*=(float scale)
    {
        X(X() * scale);
        Y(Y() * scale);
        return *this;
    }

    Vector &Vector::operator+=(const Vector &other)
    {
        X(X() + other.X());
        Y(Y() + other.Y());

        return *this;
    }

    Vector &Vector::operator-=(const Vector &other)
    {
        X(X() - other.X());
        Y(Y() - other.Y());

        return *this;
    }

    Vector &Vector::operator=(const Vector &other)
    {
        X(other.X());
        Y(other.Y());

        return *this;
    }
}
