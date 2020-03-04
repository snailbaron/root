#pragma once

#include "assets.hpp"
#include "camera.hpp"
#include "timers.hpp"
#include "world-units.hpp"

#include <SDL.h>

#include <memory>
#include <vector>

class Sprite {
public:
    Sprite(
        std::shared_ptr<SDL_Texture> texture,
        std::vector<Frame> frames,
        float frameDuration);

    void update(float delta);
    void draw(SDL_Renderer* renderer, const Camera& camera);

private:
    std::shared_ptr<SDL_Texture> _texture;
    std::vector<SDL_Rect> _frames;
    size_t _currentFrame = 0;
    FrameCounter _frameCounter;
    Position _objectPosition;
};
