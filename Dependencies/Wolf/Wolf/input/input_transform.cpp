#include "input_transform.h"
#include <GLFW/glfw3.h>

namespace Wolf
{
    namespace Input
    {
        glm::vec2 screen_to_world_coord(const Rendering::Camera& camera, glm::vec2 local)
        {
            return {
                local.x / camera.get_zoom() + camera.get_position().x,
                local.y / camera.get_zoom() + camera.get_position().y
            };
        }
        glm::vec2 world_to_screem_coord(const Rendering::Camera& camera, glm::vec2 world)
        {   
            return {
                (world.x - camera.get_position().x) * camera.get_zoom(),
                (world.y - camera.get_position().y) * camera.get_zoom()
            };
        }
    }
}