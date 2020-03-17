#pragma once

#include "entity-system.hpp"
#include "events.hpp"
#include "world-units.hpp"

#include <evening.hpp>

class World : public evening::Subscriber {
public:
    World();

    void update(Time delta);

private:
    EntityManager _es;
};
