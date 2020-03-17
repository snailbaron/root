#include "assert.hpp"
#include "config.hpp"
#include "events.hpp"
#include "player-terminal.hpp"
#include "timers.hpp"
#include "util.hpp"
#include "world.hpp"

#include <SFML/Network.hpp>

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    ASSERT(argc > 0);
    dataPath(fs::path{argv[0]}.parent_path() / "data");

    sf::TcpSocket socket;
    auto status = socket.connect("localhost", 12345);
    if (status != sf::Socket::Done) {
        std::cerr << "TCP connection failed\n";
        return 1;
    }

    auto world = World{};

    {
        evt::SpawnObject e;
        e.set_object_type(evt::OBJECT_TYPE_HOUSE);
        encode(e.mutable_position(), Position{-5_m, 5_m});
        clientRequests.push(e);
    }
    {
        evt::SpawnObject e;
        e.set_object_type(evt::OBJECT_TYPE_TREE);
        encode(e.mutable_position(), Position{5_m, 5_m});
        clientRequests.push(e);
    }
    {
        evt::SpawnObject e;
        e.set_object_type(evt::OBJECT_TYPE_PLAYER);
        encode(e.mutable_position(), Position{});
        clientRequests.push(e);
    }

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
