#pragma once

#include "world-units.hpp"

struct MovementComponent {
    Position position;
    Velocity velocity;
    Speed maxSpeed;
};

struct PlayerControlComponent {
    Acceleration force;
};
