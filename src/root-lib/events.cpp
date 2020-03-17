#include "events.hpp"

Position decode(const evt::Position& protoPosition)
{
    return {Length{protoPosition.x()}, Length{protoPosition.y()}};
}

void encode(evt::Position* protoPosition, const Position& position)
{
    protoPosition->set_x(*position.x);
    protoPosition->set_y(*position.y);
}
