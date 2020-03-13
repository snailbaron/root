#pragma once

#include "world-units.hpp"

struct MovementComponent {
    Speed maxSpeed;
    AbsoluteForce maxForce;
    AbsoluteForce friction;

    Position position;
    Velocity velocity;
    Force force;
};

struct CollisionComponent {
    Length radius;
};
