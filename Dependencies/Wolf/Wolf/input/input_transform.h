#pragma once
#ifndef WOLF_INPUT_TRANSFORM_H
#define WOLF_INPUT_TRANSFORM_H
#include <glm/glm.hpp>
#include "../rendering/Camera.h"

namespace Wolf
{
    namespace Input
    {
        
        glm::vec2 screen_to_world_coord(const Rendering::Camera& camera, glm::vec2 local);
        glm::vec2 world_to_screem_coord(const Rendering::Camera& camera, glm::vec2 world);
    }
}

#endif