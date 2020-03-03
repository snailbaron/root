#pragma once

#include "world-units.hpp"

struct WorldConfig {
    Speed maxPlayerSpeed = 3_mps;
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
