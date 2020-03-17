#pragma once

#include "world-units.hpp"

struct WorldConfig {
    Speed maxPlayerSpeed = 8_mps;
    Time timeToFullSpeed = 0.25_s;
    Time timeToFullStop = 0.25_s;

    AbsoluteForce playerFriction = maxPlayerSpeed / timeToFullStop;
    AbsoluteAcceleration maxPlayerAcceleration =
        playerFriction + maxPlayerSpeed / timeToFullSpeed;
};

WorldConfig& mutableWorldConfig()
{
    static WorldConfig worldConfig;
    return worldConfig;
}

const WorldConfig& worldConfig()
{
    return mutableWorldConfig();
}
