#include "assets.hpp"
#include "config.hpp"
#include "events.hpp"
#include "player-terminal.hpp"

PlayerTerminal::PlayerTerminal()
{
    _window.create(
        {config().windowWidth, config().windowHeight},
        config().windowTitle);

    float hspan = config().cameraHorizontalSpanMeters;
    float vspan = hspan * config().windowHeight / config().windowWidth;
    _camera.setSize(hspan, vspan);

    subscribe<PlayerSpawned>(worldEvents, [this] (const auto& playerSpawned) {
        auto sprite = _resources.createSprite(Bitmap::FarmerStandingDown);
        sprite.setPosition(*playerSpawned.position.x, *playerSpawned.position.y);
        _sprites[playerSpawned.entity] = std::move(sprite);
    });
    subscribe<PositionUpdated>(worldEvents, [this] (const auto& e) {
        _sprites.at(e.entity).setPosition(*e.position.x, *e.position.y);
    });
}

bool PlayerTerminal::isAlive() const
{
    return _window.isOpen();
}

void PlayerTerminal::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                _window.close();
                break;

            default:
                break;
        }
    }
}

void PlayerTerminal::update(float /*delta*/)
{
}

void PlayerTerminal::render()
{
    _window.clear();

    _window.setView(_camera);
    for (const auto& [entity, sprite] : _sprites) {
        _window.draw(sprite);
    }

    _window.display();
}
