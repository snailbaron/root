// TODO: generate this file automatically

#pragma once

#include <map>
#include <string>
#include <vector>

enum class Bitmap {
    FarmerStandingDown,
    FarmerWalkingUp,
    Grass,
};

inline Bitmap bitmapByName(const std::string& bitmapName)
{
    std::map<std::string, Bitmap> mapping {
        {"farmer-standing-down", Bitmap::FarmerStandingDown},
        {"farmer-walking-up", Bitmap::FarmerWalkingUp},
        {"grass", Bitmap::Grass},
    };
    return mapping.at(bitmapName);
}
