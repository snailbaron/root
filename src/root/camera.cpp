#include "camera.hpp"

Length Camera::hspan() const
{
    return _span.x;
}

void Camera::hspan(Length hspan)
{
    auto centerPosition = _topLeftCorner + _span / 2.f;
    _span.x = hspan;
    this->position(centerPosition);
}

Length Camera::vspan() const
{
    return _span.y;
}

void Camera::vspan(Length vspan)
{
    auto centerPosition = _topLeftCorner + _span / 2;
    _span.y = vspan;
    this->position(centerPosition);
}

void Camera::screenSize(ScreenSize screenSize)
{
    _screenSize = screenSize;
}

void Camera::position(const Position& centerPosition)
{
    _topLeftCorner = centerPosition - _span / 2;
}

ScreenPoint Camera::project(Position position) const
{
    ScreenPoint p;
    p.x = *((position.x - _topLeftCorner.x) * _screenSize.w / _span.x);
    p.y = *((_topLeftCorner.y - position.y) * _screenSize.h / _span.y);
    return p;
}
