#pragma once

#include "type_traits.hpp"

#include <cmath>
#include <ostream>
#include <type_traits>

namespace units {

template <class Type, int L, int M, int T>
class Unit {
    static_assert(std::is_arithmetic<Type>());

public:
    Unit() {}

    template <
        class U,
        std::enable_if_t<
            std::is_convertible_v<U, Type> && L == 0 && M == 0 && T == 0,
            int> = 0>
    constexpr Unit(U value)
        : _value(value)
    { }

    template <
        class U,
        std::enable_if_t<
            std::is_convertible_v<U, Type> && (L != 0 || M != 0 || T != 0),
            int> = 0>
    constexpr explicit Unit(U value)
        : _value(value)
    { }

    template <
        int _L = L, int _M = M, int _T = T,
        class = std::enable_if_t<_L == 0 && _M == 0 && _T == 0>>
    operator Type() const
    {
        return _value;
    }

    template <class U, class = std::enable_if_t<std::is_convertible_v<U, Type>>>
    Unit(Unit<U, L, M, T> other)
        : _value(other._value)
    { }

    Type operator*() const
    {
        return _value;
    }

    Unit operator-()
    {
        return Unit{-_value};
    }

    Unit& operator+=(const Unit& other)
    {
        _value += other._value;
        return *this;
    }

    Unit& operator-=(const Unit& other)
    {
        _value -= other._value;
        return *this;
    }

    template <
        class S,
        class = std::enable_if_t<std::is_convertible_v<S, Type>>>
    Unit& operator*=(const S& scalar)
    {
        _value *= scalar;
        return *this;
    }

    Unit& operator*=(const Unit<Type, 0, 0, 0>& scalarUnit)
    {
        return this->operator*=(*scalarUnit);
    }

    template <
        class S,
        class = std::enable_if_t<std::is_convertible_v<S, Type>>>
    Unit& operator/=(const S& scalar)
    {
        _value /= scalar;
        return *this;
    }

    Unit& operator/=(const Unit<Type, 0, 0, 0>& scalarUnit)
    {
        return this->operator/=(*scalarUnit);
    }

private:
    Type _value {};
};

template <class Type, int L, int M, int T>
auto operator+(Unit<Type, L, M, T> lhs, const Unit<Type, L, M, T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template <class Type, int L, int M, int T>
auto operator-(Unit<Type, L, M, T> lhs, const Unit<Type, L, M, T>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template <class Type, int L1, int M1, int T1, int L2, int M2, int T2>
auto operator*(Unit<Type, L1, M1, T1> lhs, Unit<Type, L2, M2, T2> rhs)
{
    return Unit<Type, L1 + L2, M1 + M2, T1 + T2>{*lhs * *rhs};
}

template <
    class Type, int L, int M, int T, class S,
    class = std::enable_if_t<std::is_arithmetic_v<S>>>
auto operator*(Unit<Type, L, M, T> unit, S scalar)
{
    return Unit<mul_type_t<Type, S>, L, M, T>{*unit * scalar};
}

template <
    class S, class Type, int L, int M, int T,
    class = std::enable_if_t<std::is_arithmetic_v<S>>>
auto operator*(S scalar, Unit<Type, L, M, T> unit)
{
    return Unit<mul_type_t<S, Type>, L, M, T>{scalar * *unit};
}

template <class Type, int L1, int M1, int T1, int L2, int M2, int T2>
auto operator/(Unit<Type, L1, M1, T1> lhs, Unit<Type, L2, M2, T2> rhs)
{
    return Unit<Type, L1 - L2, M1 - M2, T1 - T2>{*lhs / *rhs};
}

template <
    class Type, int L, int M, int T, class S,
    class = std::enable_if_t<std::is_arithmetic_v<S>>>
auto operator/(Unit<Type, L, M, T> unit, S scalar)
{
    return Unit<div_type_t<Type, S>, L, M, T>{*unit / scalar};
}

template <
    class Type, int L, int M, int T,
    class = std::enable_if_t<L % 2 == 0 && M % 2 == 0 && T % 2 == 0>>
auto sqrt(Unit<Type, L, M, T> unit)
{
    return Unit<Type, L / 2, M / 2, T / 2>{std::sqrt(*unit)};
}

template <class Type, int L, int M, int T>
bool operator==(const Unit<Type, L, M, T>& lhs, const Unit<Type, L, M, T>& rhs)
{
    return *lhs == *rhs;
}

template <class Type, int L, int M, int T>
bool operator!=(const Unit<Type, L, M, T>& lhs, const Unit<Type, L, M, T>& rhs)
{
    return !(lhs == rhs);
}

template <class Type, int L, int M, int T>
bool operator<(const Unit<Type, L, M, T>& lhs, const Unit<Type, L, M, T>& rhs)
{
    return *lhs < *rhs;
}

template <class Type, int L, int M, int T>
bool operator>(const Unit<Type, L, M, T>& lhs, const Unit<Type, L, M, T>& rhs)
{
    return rhs < lhs;
}

template <class Type, int L, int M, int T>
bool operator<=(const Unit<Type, L, M, T>& lhs, const Unit<Type, L, M, T>& rhs)
{
    return !(lhs > rhs);
}

template <class Type, int L, int M, int T>
bool operator>=(const Unit<Type, L, M, T>& lhs, const Unit<Type, L, M, T>& rhs)
{
    return !(lhs < rhs);
}

template <class Type, int L, int M, int T>
std::ostream& operator<<(std::ostream& output, const Unit<Type, L, M, T>& unit)
{
    if constexpr (L == 0 && M == 0 && T == 0) {
        return output << *unit;
    } else if constexpr (L == 1 && M == 0 && T == 0) {
        return output << *unit << " m";
    } else if constexpr (L == 1 && M == 0 && T == -1) {
        return output << *unit << " m/s";
    } else if constexpr (L == 1 && M == 0 && T == -2) {
        return output << *unit << " m/s²";
    } else {
        return output << *unit << " L^" << L << "M^" << M << "T^" << T;
    }
}

template <class Type>
using Length = Unit<Type, 1, 0, 0>;

template <class Type>
using Speed = Unit<Type, 1, 0, -1>;

template <class Type>
using Acceleration = Unit<Type, 1, 0, -2>;

template <class Type>
using Time = Unit<Type, 0, 0, 1>;

} // namespace units
