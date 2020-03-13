#pragma once

#include "entity-system.hpp"
#include "world-units.hpp"

#include <evening.hpp>

inline evening::Channel worldEvents;
inline evening::Channel clientRequests;

struct SpawnPlayer {};

struct MovePlayer {
    Entity entity;
    Vector2 control;
};

struct PositionUpdated {
    Entity entity;
    Position position;
};

struct PlayerSpawned {
    Entity entity;
    Position position;
};
