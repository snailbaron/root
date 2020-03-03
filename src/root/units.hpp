#pragma once

#include <utility>

namespace units {

template <class Type, int L, int M, int T>
class Unit {
public:
    explicit constexpr Unit(Type&& value)
        : _value(std::forward(value))
    { }

    constexpr const Type& operator*() const
    {
        return _value;
    }

private:
    Type _value;
};

template <class Type>
using Length = Unit<Type, 1, 0, 0>;

template <class Type>
using Speed = Unit<Type, 1, 0, -1>;

template <class Type>
using Acceleration = Unit<Type, 1, 0, -2>;

template <class Type>
using Time = Unit<Type, 0, 0, 1>;

} // namespace units
