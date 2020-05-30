#pragma once
#include <cmath>

constexpr float EPSILON = 0.0001f;

inline bool Equals(float a, float b)
{
    if (std::isinf(a) || std::isinf(b))
    {
        return a == b;
    }
    return std::abs(a - b) < EPSILON;
}

