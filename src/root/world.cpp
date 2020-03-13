#include "log.hpp"
#include "world-components.hpp"
#include "world-config.hpp"
#include "world.hpp"

#include <iterator>

World::World()
{
    subscribe<SpawnObject>(clientRequests, [this] (const auto& request) {
        log() << "spawn requested\n";

        auto object = _es.createEntity();

        auto& movement = _es.add<MovementComponent>(object);
        if (request.objectType == ObjectType::Player) {
            movement.maxSpeed = worldConfig().maxPlayerSpeed;
            movement.maxForce = worldConfig().maxPlayerAcceleration;
            movement.friction = worldConfig().playerFriction;
        }
        movement.position = request.position;

        auto& collision = _es.add<CollisionComponent>(object);
        collision.radius = 1_m;

        worldEvents.push(
            ObjectSpawned{object, request.objectType, movement.position});
    });

    subscribe<MovePlayer>(clientRequests, [this] (const auto& request) {
        auto movement = _es.component<MovementComponent>(request.entity);
        movement->force = {
            request.control.x * movement->maxForce,
            request.control.y * movement->maxForce
        };
        movement->force.limit(movement->maxForce);
    });

    subscribe<PlantTree>(clientRequests, [this] (const auto& request) {
        log() << "plant requested\n";

        auto movement = _es.component<MovementComponent>(request.player);
        clientRequests.send(SpawnObject{ObjectType::Tree, movement->position});
    });
}

void World::update(Time delta)
{
    for (auto e : _es.entities<MovementComponent>()) {
        log() << "entity with movement: " << e << "\n";

        auto movement = _es.component<MovementComponent>(e);

        movement->velocity += movement->force * delta;
        movement->velocity.shortenBy(movement->friction * delta);
        movement->velocity.limit(movement->maxSpeed);
        movement->position += movement->velocity * delta;
        worldEvents.push(PositionUpdated{e, movement->position});
    }

    {
        const auto& es = _es.entities<CollisionComponent>();
        for (auto i = es.begin(); i != es.end(); ++i) {
            for (auto j = std::next(i); j != es.end(); ++j) {
                auto mi = _es.component<MovementComponent>(*i);
                auto mj = _es.component<MovementComponent>(*j);
                auto ci = _es.component<CollisionComponent>(*i);
                auto cj = _es.component<CollisionComponent>(*j);

                auto overlap = ci->radius + cj->radius -
                    distance(mi->position, mj->position);
                if (overlap > 0_m) {
                    if (mi->maxSpeed > 0_mps) {
                        mi->position += unit(mi->position - mj->position) * overlap;
                    } else if (mj->maxSpeed > 0_mps) {
                        mj->position += unit(mj->position - mi->position) * overlap;
                    }
                }
            }
        }
    }
}
