#include "assets.hpp"
#include "config.hpp"
#include "events.hpp"
#include "log.hpp"
#include "player-terminal.hpp"

#include <cmath>

PlayerTerminal::PlayerTerminal()
{
    _window.create(
        {config().windowWidth, config().windowHeight},
        config().windowTitle);
    _window.setKeyRepeatEnabled(false);

    _camera.setSize(
        sf::Vector2f{_window.getSize()} /
            static_cast<float>(config().pixelation) /
            config().pixelsInMeter);
    _camera.setSize(_camera.getSize().x, -_camera.getSize().y);
    _camera.setCenter(0.f, 0.f);
    log() << "camera size: " << _camera.getSize().x << ", " <<
        _camera.getSize().y << "\n";

    {
        const auto& grassFrame = _resources.frame(Bitmap::Grass);

        auto w = grassFrame.width / config().pixelsInMeter;
        auto h = grassFrame.height / config().pixelsInMeter;

        auto xn =
            _window.getSize().x / (grassFrame.width * config().pixelation) + 2;
        auto yn =
            _window.getSize().y / (grassFrame.height * config().pixelation) + 2;
        auto x0 = -w * xn / 2.f;
        auto y0 = -h * yn / 2.f;

        _background.setPrimitiveType(sf::Quads);
        _background.resize(xn * yn * 4);
        for (unsigned x = 0; x < xn; x++) {
            for (unsigned y = 0; y < yn; y++) {
                auto cell = &_background[4 * (x + y * xn)];

                cell[0].position = {x0 + x * w, y0 + y * h};
                cell[1].position = {x0 + (x + 1) * w, y0 + y * h};
                cell[2].position = {x0 + (x + 1) * w, y0 + (y + 1) * h};
                cell[3].position = {x0 + x * w, y0 + (y + 1) * h};

                cell[0].texCoords = {1.f * grassFrame.left, 1.f * grassFrame.top + grassFrame.height};
                cell[1].texCoords = {1.f * grassFrame.left + grassFrame.width, 1.f * grassFrame.top + grassFrame.height};
                cell[2].texCoords = {1.f * grassFrame.left + grassFrame.width, 1.f * grassFrame.top};
                cell[3].texCoords = {1.f * grassFrame.left, 1.f * grassFrame.top};
            }
        }
    }

    subscribe<PlayerSpawned>(worldEvents, [this] (const auto& playerSpawned) {
        auto sprite = _resources.createSprite(Bitmap::FarmerStandingDown);
        sprite.setPosition(*playerSpawned.position.x, *playerSpawned.position.y);
        _sprites[playerSpawned.entity] = std::move(sprite);
        _playerEntity = playerSpawned.entity;
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
        if (event.type == sf::Event::Closed) {
            _window.close();
        } else if (event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::KeyReleased) {
            if (_playerEntity && (
                    event.key.code == config().moveUp ||
                    event.key.code == config().moveDown ||
                    event.key.code == config().moveLeft ||
                    event.key.code == config().moveRight)) {
                auto request = MovePlayer{*_playerEntity, {}};
                if (sf::Keyboard::isKeyPressed(config().moveRight)) {
                    request.control.x += 1.f;
                }
                if (sf::Keyboard::isKeyPressed(config().moveLeft)) {
                    request.control.x -= 1.f;
                }
                if (sf::Keyboard::isKeyPressed(config().moveUp)) {
                    request.control.y += 1.f;
                }
                if (sf::Keyboard::isKeyPressed(config().moveDown)) {
                    request.control.y -= 1.f;
                }
                clientRequests.push(request);
            }
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

    _window.draw(_background, sf::RenderStates{&_resources.megaTexture()});

    for (const auto& [entity, sprite] : _sprites) {
        _window.draw(sprite);
    }

    _window.display();
}
