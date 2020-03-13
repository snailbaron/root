// TODO: generate this file automatically

#pragma once

#include <map>
#include <string>
#include <vector>

enum class Bitmap {
    FarmerStandingDown,
    FarmerWalkingUp,
    Grass,
    House,
    Tree,
};

inline Bitmap bitmapByName(const std::string& bitmapName)
{
    std::map<std::string, Bitmap> mapping {
        {"farmer-standing-down", Bitmap::FarmerStandingDown},
        {"farmer-walking-up", Bitmap::FarmerWalkingUp},
        {"grass", Bitmap::Grass},
        {"house", Bitmap::House},
        {"tree", Bitmap::Tree},
    };
    return mapping.at(bitmapName);
}
