#include "log.hpp"
#include "world-components.hpp"
#include "world-config.hpp"
#include "world.hpp"

World::World()
{
    subscribe<SpawnPlayer>(clientRequests, [this] (const auto&) {
        auto player = _es.createEntity();

        auto& movement = _es.add<MovementComponent>(player);
        movement.maxSpeed = worldConfig().maxPlayerSpeed;
        movement.maxForce = worldConfig().maxPlayerAcceleration;
        movement.friction = worldConfig().playerFriction;

        worldEvents.push(PlayerSpawned{player, movement.position});
    });

    subscribe<MovePlayer>(clientRequests, [this] (const auto& request) {
        auto movement = _es.component<MovementComponent>(request.entity);
        movement->force = {
            request.control.x * movement->maxForce,
            request.control.y * movement->maxForce
        };
        movement->force.limit(movement->maxForce);
    });
}

void World::update(Time delta)
{
    for (auto e : _es.entities<MovementComponent>()) {
        auto movement = _es.component<MovementComponent>(e);

        movement->velocity += movement->force * delta;
        movement->velocity.shortenBy(movement->friction * delta);
        movement->velocity.limit(movement->maxSpeed);
        movement->position += movement->velocity * delta;
        worldEvents.push(PositionUpdated{e, movement->position});

        log() << "movement: " << movement->force << " " << movement->velocity <<
            " " << movement->position << "\n";
    }
}
