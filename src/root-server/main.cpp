#include "world.hpp"

#include <SFML/Network.hpp>

#include <iostream>

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    sf::TcpListener listener;

    if (listener.listen(12345) != sf::Socket::Done) {
        std::cerr << "TCP listen attempt failed\n";
        return 1;
    }

    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done) {
        std::cerr << "failed to accept a connection from client\n";
        return 1;
    }

    auto world = World{};
}
