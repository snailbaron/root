#pragma once

#include <type_traits>

namespace units {

template <class Type, int L, int M, int T>
class Unit {
    static_assert(std::is_arithmetic<Type>());

public:
    Unit()
        : _value()
    { }

    template <
        int _L = L, int _M = M, int _T = T,
        class = std::enable_if_t<_L == 0 && _M == 0 && _T == 0>>
    constexpr Unit(Type value)
        : _value(value)
    { }

    template <
        int _L = L, int _M = M, int _T = T,
        class = std::enable_if_t<_L != 0 || _M != 0 || _T != 0>>
    constexpr explicit Unit(Type value)
        : _value(value)
    { }

    template <class U, class = std::enable_if_t<std::is_convertible_v<U, Type>>>
    Unit(Unit<U, L, M, T> other)
        : _value(other._value)
    { }

    Type operator*() const
    {
        return _value;
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

private:
    Type _value;
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

template <class Type>
using Length = Unit<Type, 1, 0, 0>;

template <class Type>
using Speed = Unit<Type, 1, 0, -1>;

template <class Type>
using Acceleration = Unit<Type, 1, 0, -2>;

template <class Type>
using Time = Unit<Type, 0, 0, 1>;

} // namespace units
