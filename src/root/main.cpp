#include "assert.hpp"
#include "config.hpp"
#include "player-terminal.hpp"
#include "timers.hpp"
#include "util.hpp"
#include "world.hpp"

#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    ASSERT(argc > 0);
    dataPath(fs::path{argv[0]});

    auto world = World{};

    auto playerTerminal = PlayerTerminal{};
    auto timer = FrameTimer{config().fps};
    for (;;) {
        playerTerminal.processEvents();
        if (!playerTerminal.isAlive()) {
            break;
        }

        auto framesPassed = timer();
        for (auto i = framesPassed; i > 0; i--) {
            world.update(Time{timer.delta()});
        }

        playerTerminal.update(framesPassed * timer.delta());
        playerTerminal.render();
    }
}
