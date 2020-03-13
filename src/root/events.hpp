#pragma once

#include "entity-system.hpp"
#include "world-units.hpp"

#include <evening.hpp>

inline evening::Channel worldEvents;
inline evening::Channel clientRequests;

enum ObjectType {
    House,
    Player,
    Tree,
};

struct SpawnObject {
    ObjectType objectType;
    Position position;
};

struct PlantTree {
    Entity player;
};

struct MovePlayer {
    Entity entity;
    Vector2 control;
};

struct PositionUpdated {
    Entity entity;
    Position position;
};

struct ObjectSpawned {
    Entity entity;
    ObjectType objectType;
    Position position;
};
