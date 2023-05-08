#include "input.h"
#include <GLFW/glfw3.h>
#include "../core/Application.h"


namespace Wolf
{
    namespace Input
    {
        glm::vec2 get_mouse_pos()
        {
            double x, y;
            Wolf::Window* window = Application::get()->get_main_window();
            glfwGetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), &x, &y);
            return {x, y};
        }
        void set_mouse_pos(glm::vec2 pos)
        {
            Wolf::Window* window = Application::get()->get_main_window();
            glfwSetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), pos.x, pos.y);
        }

        glm::vec2 get_mouse_pos_norm()
        {
            double x_pixel, y_pixel;
            Wolf::Window* window = Application::get()->get_main_window();
            glfwGetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), &x_pixel, &y_pixel);

            float norm_x = x_pixel / static_cast<double>(window->get_width());
            float norm_y = y_pixel / static_cast<double>(window->get_height());

            return {(norm_x - 0.5) * 2, ((1 - norm_y) - 0.5) * 2};
        }
        void set_mouse_pos_norm(glm::vec2 pos)
        {
            Wolf::Window* window = Application::get()->get_main_window();
            uint32_t x = ((pos.x + 1.0) / 2.0) * window->get_width();
            uint32_t y = (1 - (pos.y + 1.0) / 2.0) * window->get_width();
            glfwSetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), x, y);
        }
    

    }
}