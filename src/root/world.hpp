#pragma once

#include "entity-system.hpp"

class World {
public:
    void update(float delta);

private:
    EntityManager _entities;
};
