#include "config.hpp"
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

    SDL_RenderPresent(_renderer.get());
}
