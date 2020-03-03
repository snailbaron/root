#pragma once

#include <type_traits>
#include <utility>

namespace geometry {

template <class U, class V>
struct sum_type {
    using type = decltype(std::declval<U>() + std::declval<V>());
};
template <class U, class V>
using sum_type_t = typename sum_type<U, V>::type;

template <class U, class V>
struct diff_type {
    using type = decltype(std::declval<U>() - std::declval<V>());
};
template <class U, class V>
using diff_type_t = typename diff_type<U, V>::type;

template <class U, class V>
struct mul_type {
    using type = decltype(std::declval<U>() * std::declval<V>());
};
template <class U, class V>
using mul_type_t = typename mul_type<U, V>::type;

template <class U, class V>
struct div_type {
    using type = decltype(std::declval<U>() / std::declval<V>());
};
template <class U, class V>
using div_type_t = typename div_type<U, V>::type;

template <class T>
struct Vector {
    Vector& operator+=(const Vector& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector& operator-=(const Vector& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector& operator*=(const T& scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    T x;
    T y;
};

template <class T>
Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class T>
Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class T, class S>
Vector<mul_type_t<T, S>> operator*(Vector<T> vector, const S& scalar)
{
    return {vector.x * scalar, vector.y * scalar};
}

template <class T, class S>
Vector<std::common_type<T, S>> operator*(const S& scalar, Vector<T> vector)
{
    return vector * scalar;
}

} // namespace geometry
