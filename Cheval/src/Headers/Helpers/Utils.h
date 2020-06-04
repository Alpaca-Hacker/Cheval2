#pragma once
#include <cmath>
#include <algorithm>

constexpr float EPSILON = 0.0001f;
constexpr float PI = 3.14159265359f;
constexpr float PIDIV2 = PI / 2.f;
constexpr float PIDIV3 = PI / 3.f;
constexpr float PIDIV4 = PI / 4.f;
constexpr float PIDIV6 = PI / 6.f;

constexpr float SQRT2 = 1.414213562373f; 
constexpr float SQRT2DIV2 = SQRT2 / 2.f; 

constexpr float INF = std::numeric_limits<float>::infinity();

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


