#pragma once
#ifndef WOLF_INTERPOLATION_H
#define WOLF_INTERPOLATION_H

#include <glm/glm.hpp>

namespace Wolf
{
    namespace Numerical
    {
        template<typename T>
        static T lerp(T a, T b, float t)
        {
            return a + (b - a) * t;
        }

        template<typename T>
        static T lerp3(T a, T b, T c, float t)
        {
            if (t < 0.5)
                return lerp(a, b, t * 2.0f);
            return lerp(b, c, (t - 0.5f) * 2.0f);
        }

        template<typename T>
        static T clamp(T value, T min, T max)
        {
            if (value > max)
                return max;

            return value < min ? min : value;
        }

    }
}


#endif