#include "world-components.hpp"
#include "world.hpp"

void World::update(Time delta)
{
    for (auto& movement : _entities.components<MovementComponent>()) {
        movement.velocity += movement.acceleration * delta;
        movement.position += movement.velocity * delta;
    }
}
