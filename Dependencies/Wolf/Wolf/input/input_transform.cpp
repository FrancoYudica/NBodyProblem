#include "input_transform.h"
#include <GLFW/glfw3.h>

namespace Wolf
{
    namespace Input
    {
        glm::vec2 get_world_coordinates(const Rendering::Camera& camera, glm::vec2 local)
        {
            return {
                camera.get_aspect_ratio() * local.x / camera.get_zoom() + camera.get_position().x,
                local.y / camera.get_zoom() + camera.get_position().y
            };
        }
        glm::vec2 get_local_coordinates(const Rendering::Camera& camera, glm::vec2 world)
        {   
            return {
                (world.x - camera.get_position().x) * camera.get_zoom() / camera.get_aspect_ratio(),
                (world.y - camera.get_position().y) * camera.get_zoom()
            };
        }
    }
}