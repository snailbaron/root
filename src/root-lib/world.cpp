#include "log.hpp"
#include "world-components.hpp"
#include "world-config.hpp"
#include "world.hpp"

#include <iterator>

World::World()
{
    subscribe<evt::SpawnObject>(clientRequests, [this] (const auto& request) {
        log() << "spawn requested\n";

        auto object = _es.createEntity();

        auto& movement = _es.add<MovementComponent>(object);
        if (request.object_type() == evt::OBJECT_TYPE_PLAYER) {
            movement.maxSpeed = worldConfig().maxPlayerSpeed;
            movement.maxForce = worldConfig().maxPlayerAcceleration;
            movement.friction = worldConfig().playerFriction;
        }
        movement.position = decode(request.position());

        auto& collision = _es.add<CollisionComponent>(object);
        collision.radius = 1_m;

        evt::ObjectSpawned e;
        e.set_entity(object);
        e.set_object_type(request.object_type());
        encode(e.mutable_position(), movement.position);
        worldEvents.push(e);
    });

    subscribe<evt::MovePlayer>(clientRequests, [this] (const auto& request) {
        auto movement = _es.component<MovementComponent>(
            Entity{request.player_entity()});
        movement->force = {
            request.control().x() * movement->maxForce,
            request.control().y() * movement->maxForce
        };
        movement->force.limit(movement->maxForce);
    });

    subscribe<evt::PlantTree>(clientRequests, [this] (const auto& request) {
        log() << "plant requested\n";

        auto movement = _es.component<MovementComponent>(
            Entity{request.player_entity()});

        evt::SpawnObject e;
        e.set_object_type(evt::OBJECT_TYPE_TREE);
        encode(e.mutable_position(), movement->position);
        clientRequests.send(e);
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

        evt::PositionUpdated event;
        event.set_entity(e);
        event.mutable_position()->set_x(*movement->position.x);
        event.mutable_position()->set_y(*movement->position.y);
        worldEvents.push(event);
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
