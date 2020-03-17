#pragma once

#include "events.pb.h"
#include "world-units.hpp"

#include <evening.hpp>

inline evening::Channel clientRequests;
inline evening::Channel worldEvents;

Position decode(const evt::Position& protoPosition);
void encode(evt::Position* protoPosition, const Position& position);
