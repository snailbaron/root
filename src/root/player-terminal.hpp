#pragma once

#include <SDL.h>

#include <memory>

class PlayerTerminal {
public:
    PlayerTerminal();

    bool isAlive() const;

    void processEvents();
    void update(float delta);
    void render();

private:
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> _window;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> _renderer;
    bool _isAlive = true;
};
