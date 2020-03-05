// TODO: generate this file automatically

#pragma once

#include <vector>

enum class Bitmap {
    FarmerStandingDown,
    FarmerWalkingUp,
    Grass,
};

struct Frame {
    int x;
    int y;
    int w;
    int h;
};

std::vector<Frame> bitmapFrames(Bitmap bitmapId)
{
    switch (bitmapId) {
        case Bitmap::FarmerStandingDown:
            return {
                {0, 0, 16, 16},
            };
        case Bitmap::FarmerWalkingUp:
            return {
                {0, 0, 16, 16},
                {0, 16, 16, 16},
            };
        case Bitmap::Grass:
            return {
                {16, 16, 16, 16},
            };
        default:
            return {};
    }
}
