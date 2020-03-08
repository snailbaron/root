#pragma once

#include <string>

struct Config {
    std::string windowTitle = "Root";
    unsigned windowWidth = 1024;
    unsigned windowHeight = 768;
    int fps = 60;
    float pixelsInMeter = 10.f;
    int pixelation = 4;

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
