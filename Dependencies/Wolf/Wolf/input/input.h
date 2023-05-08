#ifndef WOLF_INPUT_H
#define WOLF_INPUT_H
#include <glm/glm.hpp>

namespace Wolf
{
    namespace Input
    {
        glm::vec2 get_mouse_pos();
        void set_mouse_pos(glm::vec2 pos);

        // Returns the position of the mouse relative to [-1, 1] space
        glm::vec2 get_mouse_pos_norm();
        void set_mouse_pos_norm(glm::vec2 pos);
    }
}

#endif