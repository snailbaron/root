#pragma once

#include "entity-system.hpp"
#include "world-units.hpp"

#include <evening.hpp>

evening::Channel worldEvents;
evening::Channel clientEvents;

struct PositionUpdate {
    Entity entity;
    Position position;
};
