#ifndef WOLF_INPUT_H
#define WOLF_INPUT_H
#include <glm/glm.hpp>
#include "../core/codes.h"	

namespace Wolf
{
    namespace Input
    {
        glm::vec2 get_pixel_mouse_pos();
        void set_pixel_mouse_pos(glm::vec2 pos);


        /// @brief Takes into consideration aspect ratio
        /// @return x in [-as, as], and y in [-1, 1] ranges
        glm::vec2 get_mouse_pos();
        glm::vec2 set_mouse_pos(glm::vec2 pos);


        /// @brief Mouse position, but normalized
        /// @return in range [-1, 1] in both axis
        glm::vec2 get_mouse_pos_norm();

        void set_mouse_pos_norm(glm::vec2 pos);

        bool is_key_down(KeyCode code);
        bool is_button_down(MouseButton code);
    }
}

#endif