#pragma once

#include "entity-system.hpp"
#include "resources.hpp"

#include <evening.hpp>

#include <SFML/Graphics.hpp>

#include <optional>
#include <map>

class PlayerTerminal : public evening::Subscriber {
public:
    PlayerTerminal();

    bool isAlive() const;

    void processEvents();
    void update(float delta);
    void render();

private:
    sf::RenderWindow _window;
    sf::View _camera;
    std::map<Entity, sf::Sprite> _sprites;
    sf::VertexArray _background;
    Resources _resources;
    std::optional<Entity> _playerEntity;
};
