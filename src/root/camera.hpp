#pragma once

#include "screen-units.hpp"
#include "world-units.hpp"

class Camera {
public:
    Length hspan() const;
    void hspan(Length hspan);

    Length vspan() const;
    void vspan(Length vspan);

    void screenSize(ScreenSize screenSize);
    void position(const Position& centerPosition);

    ScreenPoint project(Position position) const;

private:
    WorldRect _span;
    Position _topLeftCorner;
    ScreenSize _screenSize;
};
