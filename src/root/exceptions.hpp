#pragma once

#include <SDL.h>

#include <exception>

class SdlException : public std::exception {
public:
    const char* what() const noexcept override
    {
        return _what;
    }

private:
    const char* const _what = SDL_GetError();
};
