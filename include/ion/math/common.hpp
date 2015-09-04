#pragma once

#include <cmath>

namespace ion { namespace math
{
    const double PI = std::atan(1.0) * 4;

    inline float radians(const float& degrees)
    {
        return degrees * (static_cast<float>(PI) / 180);
    }

    inline float degrees(const float& radians)
    {
        return radians * (180 / static_cast<float>(PI));
    }
}}