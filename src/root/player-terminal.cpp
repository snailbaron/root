#include "config.hpp"
#include "events.hpp"
#include "exceptions.hpp"
#include "player-terminal.hpp"

PlayerTerminal::PlayerTerminal()
    : _window(nullptr, SDL_DestroyWindow)
    , _renderer(nullptr, SDL_DestroyRenderer)
{
    _window.reset(SDL_CreateWindow(
        config().windowTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        config().windowWidth,
        config().windowHeight,
        0));
    if (!_window) {
        throw SdlException{};
    }

    _renderer.reset(SDL_CreateRenderer(
        _window.get(),
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!_renderer) {
        throw SdlException{};
    }

    _camera.hspan(Length{config().cameraHorizontalSpanMeters});
    _camera.vspan(
        _camera.hspan() * config().windowHeight / config().windowWidth);
    _camera.screenSize({config().windowWidth, config().windowHeight});

    subscribe<PlayerSpawned>(worldEvents, [this] (const auto& playerSpawned) {
        auto sprite = createSprite(Bitmap::Farmer);
        sprite.position = playerSpawned.position;
        _sprites[playerSpawned.entity] = std::move(sprite);
    });
    subscribe<PositionUpdated>(worldEvents, [this] (const auto& e) {
        _sprites.at(e.entity).position = e.position;
    });
}

bool PlayerTerminal::isAlive() const
{
    return _isAlive;
}

void PlayerTerminal::processEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _isAlive = false;
                break;
        }
    }
}

void PlayerTerminal::update(float /*delta*/)
{
}

void PlayerTerminal::render()
{
    SDL_SetRenderDrawColor(_renderer.get(), 50, 50, 50, 255);
    SDL_RenderClear(_renderer.get());

    for (const auto& [entity, sprite] : _sprites) {
        sprite.draw(_renderer.get(), _camera);
    }

    SDL_RenderPresent(_renderer.get());
}
