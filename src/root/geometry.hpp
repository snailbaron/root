#pragma once

#include "type_traits.hpp"

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

    constexpr Vector& operator*=(const T& scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr Vector& operator/=(const T& scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
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

} // namespace geometry
