#pragma once
#ifndef WOLF_INPUT_TRANSFORM_H
#define WOLF_INPUT_TRANSFORM_H
#include <glm/glm.hpp>
#include "../rendering/Camera.h"

namespace Wolf
{
    namespace Input
    {
        
        glm::vec2 get_world_coordinates(const Rendering::Camera& camera, glm::vec2 local);
        glm::vec2 get_local_coordinates(const Rendering::Camera& camera, glm::vec2 world);
    }
}

#endif