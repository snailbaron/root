#include "assert.hpp"
#include "resources.hpp"
#include "util.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>

Resources::Resources()
{
    auto dataFilePath = dataPath() / "gfx-data.png";
    auto metaFilePath = dataPath() / "gfx-meta.json";

    ASSERT(_megaTexture.loadFromFile(dataFilePath));

    auto metaStream = std::ifstream{metaFilePath};
    auto metaJson = nlohmann::json{};
    metaStream >> metaJson;
    for (const auto& f : metaJson["frames"]) {
        auto rect = sf::IntRect{f["x"], f["y"], f["w"], f["h"]};

        std::string fileName = f["filename"];
        auto sep = fileName.find(':');
        auto bitmapName = fileName.substr(0, sep);
        auto bitmap = bitmapByName(bitmapName);
        auto frameIndex = static_cast<size_t>(
            std::stoull(fileName.substr(sep + 1)));
        ASSERT(frameIndex == _frames[bitmap].size());
        _frames[bitmap].push_back(rect);
    }
}

sf::Sprite Resources::createSprite(Bitmap bitmap)
{
    return {_megaTexture, _frames.at(bitmap).front()};
}
