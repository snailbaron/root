#pragma once

#include "type_traits.hpp"

#include <algorithm>
#include <cmath>
#include <ostream>
#include <utility>

namespace geometry {

template <class T>
struct Vector {
    constexpr Vector& operator+=(const Vector& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr Vector& operator-=(const Vector& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    template <class S>
    constexpr Vector& operator*=(const S& scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <class S>
    constexpr Vector& operator/=(const S& scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    void limit(const T& value)
    {
        auto sqlen = x * x + y * y;
        if (sqlen > value * value) {
            auto len = sqrt(sqlen);
            x *= value / len;
            y *= value / len;
        }
    }

    auto norm() const
    {
        return sqrt(x * x + y * y);
    }

    bool nonzero() const
    {
        return x != T{0} || y != T{0};
    }

    void shortenBy(const T& value)
    {
        if (nonzero()) {
            auto length = norm();
            auto newLength = std::max(T{0}, length - value);
            x *= newLength / length;
            y *= newLength / length;
        }
    }

    T x;
    T y;
};

template <class T>
constexpr Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
constexpr Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T, class S>
constexpr Vector<mul_type_t<T, S>> operator*(Vector<T> vector, const S& scalar)
{
    return {vector.x * scalar, vector.y * scalar};
}

template <class S, class T>
constexpr Vector<mul_type_t<S, T>> operator*(const S& scalar, Vector<T> vector)
{
    return vector * scalar;
}

template <class T, class S>
constexpr Vector<div_type_t<T, S>> operator/(Vector<T> vector, const S& scalar)
{
    return {vector.x / scalar, vector.y / scalar};
}

template <class T>
std::ostream& operator<<(std::ostream& output, const Vector<T>& vector)
{
    return output << "(" << vector.x << ", " << vector.y << ")";
}

} // namespace geometry
