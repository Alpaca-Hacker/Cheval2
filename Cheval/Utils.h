#pragma once
#include <cmath>
#include <algorithm>

constexpr float EPSILON = 0.0001f;

inline bool Equals(float a, float b)
{
    if (std::isinf(a) || std::isinf(b))
    {
        return a == b;
    }
    return std::abs(a - b) < EPSILON;
}

template<typename T>
typename std::enable_if_t<std::is_arithmetic_v<T>, T>
Clamp(T value, T min, T max)
{
    return std::max(min, std::min(max, value));
}
