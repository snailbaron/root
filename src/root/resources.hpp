#pragma once

#include "assets.hpp"

#include <SFML/Graphics.hpp>

#include <map>
#include <vector>

class Resources {
public:
    Resources();

    sf::Sprite createSprite(Bitmap bitmap);

private:
    sf::Texture _megaTexture;
    std::map<Bitmap, std::vector<sf::IntRect>> _frames;
};
