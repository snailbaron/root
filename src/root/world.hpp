#pragma once

#include "entity-system.hpp"
#include "world-units.hpp"

class World {
public:
    void update(Time delta);

private:
    EntityManager _entities;
};
