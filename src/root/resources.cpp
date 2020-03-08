#include "assert.hpp"
#include "config.hpp"
#include "log.hpp"
#include "resources.hpp"
#include "util.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>

Resources::Resources()
{
    // TODO: write these paths in cmake?
    auto dataFilePath = dataPath() / "gfx-data.png";
    auto metaFilePath = dataPath() / "gfx-meta.json";

    log() << "loading resource data file: " << dataFilePath << "\n";
    ASSERT(_megaTexture.loadFromFile(dataFilePath));

    auto metaStream = std::ifstream{metaFilePath};
    auto metaJson = nlohmann::json{};
    metaStream >> metaJson;
    for (const auto& f : metaJson.at("frames")) {
        const auto& r = f.at("frame");
        auto rect = sf::IntRect{r.at("x"), r.at("y"), r.at("w"), r.at("h")};

        std::string names = f.at("filename");
        auto s1 = names.find(':');
        auto spriteName = names.substr(0, s1);
        auto s2 = names.find(':', s1 + 1);
        auto animationName = names.substr(s1 + 1, s2 - s1 - 1);
        auto frameIndex = static_cast<size_t>(
            std::stoull(names.substr(s2 + 1)));

        auto bitmapName = spriteName;
        if (!animationName.empty()) {
            bitmapName += "-" + animationName;
        }
        auto bitmap = bitmapByName(bitmapName);

        ASSERT(frameIndex == _frames[bitmap].size());

        _frames[bitmap].push_back(rect);
    }
}

sf::Sprite Resources::createSprite(Bitmap bitmap)
{
    const auto& rect = _frames.at(bitmap).front();
    auto sprite = sf::Sprite{_megaTexture, rect};
    auto metersInPixel = 1.f / config().pixelsInMeter;
    sprite.setScale(metersInPixel, metersInPixel);
    sprite.setOrigin(rect.width / 2, rect.height / 2);
    return sprite;
}
