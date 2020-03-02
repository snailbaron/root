#include "config.hpp"
#include "exceptions.hpp"
#include "frame_timer.hpp"
#include "player-terminal.hpp"

#include <SDL.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        throw SdlException{};
    }

    auto playerTerminal = PlayerTerminal{};
    auto frameTimer = FrameTimer{config().fps};
    for (;;) {
        playerTerminal.processEvents();
        if (!playerTerminal.isAlive()) {
            break;
        }

        auto framesPassed = frameTimer();
        // TODO: update game logic in exactly 'delta' steps

        playerTerminal.update(framesPassed * frameTimer.delta());
        playerTerminal.render();
    }



    SDL_Quit();
}
