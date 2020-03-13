#pragma once

#include <string>

#include <SFML/Window.hpp>

struct Config {
    std::string windowTitle = "Root";
    unsigned windowWidth = 1024;
    unsigned windowHeight = 768;
    int fps = 60;
    float pixelsInMeter = 10.f;
    int pixelation = 4;

    sf::Keyboard::Key moveUp = sf::Keyboard::W;
    sf::Keyboard::Key moveDown = sf::Keyboard::S;
    sf::Keyboard::Key moveLeft = sf::Keyboard::A;
    sf::Keyboard::Key moveRight = sf::Keyboard::D;
    sf::Keyboard::Key plantTree = sf::Keyboard::Space;

private:
    Config() {}
    friend Config& mutableConfig();
};

inline Config& mutableConfig()
{
    static Config config;
    return config;
}

inline const Config& config()
{
    return mutableConfig();
}
