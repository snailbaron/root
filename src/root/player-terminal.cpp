#include "assets.hpp"
#include "config.hpp"
#include "events.hpp"
#include "log.hpp"
#include "player-terminal.hpp"

PlayerTerminal::PlayerTerminal()
{
    _window.create(
        {config().windowWidth, config().windowHeight},
        config().windowTitle);

    _camera.setSize(
        sf::Vector2f{_window.getSize()} /
            static_cast<float>(config().pixelation) /
            config().pixelsInMeter);
    _camera.setCenter(0.f, 0.f);
    log() << "camera size: " << _camera.getSize().x << ", " <<
        _camera.getSize().y << "\n";

    subscribe<PlayerSpawned>(worldEvents, [this] (const auto& playerSpawned) {
        auto sprite = _resources.createSprite(Bitmap::FarmerStandingDown);
        sprite.setPosition(*playerSpawned.position.x, *playerSpawned.position.y);
        _sprites[playerSpawned.entity] = std::move(sprite);
        log() << "created player sprite\n";
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
    _window.clear(sf::Color{30, 30, 30});

    _window.setView(_camera);
    for (const auto& [entity, sprite] : _sprites) {
        _window.draw(sprite);
    }

    _window.display();
}
