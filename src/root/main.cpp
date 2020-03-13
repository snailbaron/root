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
    dataPath(fs::path{argv[0]}.parent_path() / "data");

    auto world = World{};

    clientRequests.push(SpawnObject{ObjectType::House, {-5_m, 5_m}});
    clientRequests.push(SpawnObject{ObjectType::Tree, {5_m, 5_m}});
    clientRequests.push(SpawnObject{ObjectType::Player, {}});

    auto playerTerminal = PlayerTerminal{};
    auto timer = FrameTimer{config().fps};
    for (;;) {
        playerTerminal.processEvents();
        if (!playerTerminal.isAlive()) {
            break;
        }

        int framesPassed = timer();

        if (framesPassed > 0) {
            clientRequests.deliver();
            world.update(Time{timer.delta()});
            for (auto i = framesPassed; i > 1; i--) {
                world.update(Time{timer.delta()});
            }
        }

        worldEvents.deliver();
        playerTerminal.update(framesPassed * timer.delta());
        playerTerminal.render();
    }
}
