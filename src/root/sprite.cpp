#include "sprite.hpp"

#include <utility>

Sprite::Sprite(
    std::shared_ptr<SDL_Texture> texture,
    std::vector<Frame> frames,
    float frameDuration)
    : _texture(std::move(texture))
    , _frames(std::move(frames))
    , _frameCounter(frameDuration)
{ }

void Sprite::update(float delta)
{
    _currentFrame =
        (_currentFrame + _frameCounter.update(delta)) % _frames.size();
}

void Sprite::draw(SDL_Renderer* renderer, const Camera& camera)
{
    const auto& frame = _frames.at(_currentFrame);

    auto p = camera.project(_objectPosition);
    auto dstRect = SDL_Rect {
        p.x - frame.w / 2,
        p.y - frame.h / 2,
        frame.w,
        frame.h
    };

    SDL_RenderCopy(renderer, _texture.get(), frame, dstRect);
}
