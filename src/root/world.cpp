#include "world-components.hpp"
#include "world-config.hpp"
#include "world.hpp"

World::World()
{
    subscribe<SpawnPlayer>(clientRequests, [this] (const auto&) {
        auto player = _es.createEntity();

        auto& movement = _es.add<MovementComponent>(player);
        movement.maxSpeed = worldConfig().maxPlayerSpeed;

        _es.add<PlayerControlComponent>(player);
    });
}

void World::update(Time delta)
{
    for (auto e : _es.entities<MovementComponent>()) {
        auto* movement = _es.component<MovementComponent>(e);
        auto* control = _es.component<PlayerControlComponent>(e);

        if (control) {
            movement->velocity += control->force * delta;
        }
        movement->position += movement->velocity * delta;
    }
}
