#pragma once

#include "entity-system.hpp"
#include "world-units.hpp"

#include <evening.hpp>

evening::Channel worldEvents;
evening::Channel clientRequests;

struct SpawnPlayer {};

struct PositionUpdate {
    Entity entity;
    Position position;
};
