#pragma once

#include "geometry.hpp"
#include "units.hpp"

using Position = geometry::Point<units::Length<float>>;
using Velocity = geometry::Vector<units::Speed<float>>;
using Acceleration = geometry::Vector<units::Acceleration<float>>;
using Time = units::Time<float>;
