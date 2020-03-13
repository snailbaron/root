#pragma once

#include "geometry.hpp"
#include "units.hpp"

using Length = units::Length<float>;
using Position = geometry::Vector<units::Length<float>>;
using WorldRect = geometry::Vector<units::Length<float>>;
using Vector2 = geometry::Vector<float>;

using Speed = units::Speed<float>;
constexpr Speed operator "" _mps(long double mps)
{
    return Speed{static_cast<float>(mps)};
}
constexpr Speed operator "" _mps(unsigned long long mps)
{
    return Speed{static_cast<float>(mps)};
}

using Velocity = geometry::Vector<units::Speed<float>>;

using AbsoluteAcceleration = units::Acceleration<float>;
constexpr AbsoluteAcceleration operator "" _mps2(long double mps2)
{
    return AbsoluteAcceleration{static_cast<float>(mps2)};
}
constexpr AbsoluteAcceleration operator "" _mps2(unsigned long long mps2)
{
    return AbsoluteAcceleration{static_cast<float>(mps2)};
}

using Acceleration = geometry::Vector<units::Acceleration<float>>;
using Force = Acceleration;
using AbsoluteForce = AbsoluteAcceleration;

using Time = units::Time<float>;
constexpr Time operator "" _s(long double seconds)
{
    return Time{static_cast<float>(seconds)};
}
constexpr Time operator "" _s(unsigned long long seconds)
{
    return Time{static_cast<float>(seconds)};
}
