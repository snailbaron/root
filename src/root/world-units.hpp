#pragma once

#include "geometry.hpp"
#include "units.hpp"

using Length = units::Length<float>;
using Position = geometry::Vector<units::Length<float>>;
using WorldRect = geometry::Vector<units::Length<float>>;

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

using Acceleration = geometry::Vector<units::Acceleration<float>>;

using Time = units::Time<float>;
