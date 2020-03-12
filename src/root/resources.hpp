#pragma once

#include "assets.hpp"

#include <SFML/Graphics.hpp>

#include <map>
#include <vector>

class Resources {
public:
    Resources();

    const sf::Texture& megaTexture() const;
    const sf::IntRect& frame(Bitmap bitmap) const;

    sf::Sprite createSprite(Bitmap bitmap);

private:
    sf::Texture _megaTexture;
    std::map<Bitmap, std::vector<sf::IntRect>> _frames;
};
