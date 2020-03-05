#pragma once

#include <stdexcept>

#define ASSERT(EXPRESSION)                                              \
    if (!(EXPRESSION)) {                                                \
        throw std::runtime_error{"assertion failed: " #EXPRESSION};     \
    }
