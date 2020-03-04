#pragma once

#include <string>

struct Config {
    std::string windowTitle = "Root";
    int windowWidth = 1024;
    int windowHeight = 768;
    int fps = 60;
    float cameraHorizontalSpanMeters = 10.0f;

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
