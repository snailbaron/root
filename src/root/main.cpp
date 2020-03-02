#include "config.hpp"
#include "exceptions.hpp"
#include "frame_timer.hpp"
#include "player-terminal.hpp"
#include "world.hpp"

#include <SDL.h>

int main()
{
    auto world = World{};

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        throw SdlException{};
    }

    auto playerTerminal = PlayerTerminal{};
    auto timer = FrameTimer{config().fps};
    for (;;) {
        playerTerminal.processEvents();
        if (!playerTerminal.isAlive()) {
            break;
        }

        auto framesPassed = timer();
        for (auto i = framesPassed; i > 0; i--) {
            world.update(timer.delta());
        }

        playerTerminal.update(framesPassed * timer.delta());
        playerTerminal.render();
    }

    SDL_Quit();
}
