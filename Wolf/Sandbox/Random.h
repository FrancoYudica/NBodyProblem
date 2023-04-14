#pragma once
#ifndef RANDOM_H
#define RANDOM_H
#include <iostream>
#include <glm/glm.hpp>


namespace Random
{

    static float Unit()
    {
    	return static_cast<float>(rand() % 1009) / 1008.0f;
    }

    static float Signed()
    {
    	return 2.0f * Unit() - 1.0f;
    }

    static float Range(float min, float max)
    {
        return min + Unit() * (max - min);
    }

    static glm::vec2 UnitVec2()
    {
        return glm::vec2(Unit(), Unit());
    }

}

#endif