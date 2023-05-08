#include "Window.h"
#include "Application.h"
#include <GLFW/glfw3.h>


namespace Wolf
{

    bool Window::initialize(const Window::Configuration& config)
    {
        GLFWmonitor* monitor = config.fullscreen ? glfwGetPrimaryMonitor() : NULL;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* windowNativePtr = glfwCreateWindow(config.width, config.height, config.title, monitor, NULL);

        _window_ptr = windowNativePtr;

        if (!_window_ptr)
        {
            std::cout << "Unable to create GLFWwindow*" << std::endl;
            return false;
        }
        _user_data.window_ptr = this;
        glfwSetWindowUserPointer(windowNativePtr, &_user_data);


        // SETS THE EVENT CALLBACKS
        // The event lifetime is only in the duration of the callback
        // so, events shouldn't be stored, it will cause a nullptr exeption
        glfwSetCursorPosCallback(windowNativePtr, [](GLFWwindow* window, double x, double y) {
            WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
            MouseMoveEvent event(x, y);
            Application::get()->on_event(&event);
            });

        glfwSetScrollCallback(windowNativePtr, [](GLFWwindow* window, double x_offset, double y_offset){
            MouseScrollEvent event(x_offset, y_offset);
            Application::get()->on_event(&event);

        });
        glfwSetWindowCloseCallback(windowNativePtr, [](GLFWwindow* window) {
            WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
            WindowClosedEvent event(userData->window_ptr);
            Application::get()->on_event(&event);
            });

        glfwSetWindowSizeCallback(windowNativePtr, [](GLFWwindow* window, int width, int height) {
            WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
            WindowResizeEvent event(width, height);
            Application::get()->on_event(&event);
            });

        glfwSetMouseButtonCallback(windowNativePtr, [](GLFWwindow* window, int button, int action, int mods) {


            MouseButton btn;
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
                btn = MouseButton::LEFT;
                break;

            case GLFW_MOUSE_BUTTON_RIGHT:
                btn = MouseButton::RIGHT;
                break;

            case GLFW_MOUSE_BUTTON_MIDDLE:
                btn = MouseButton::RIGHT;
                break;

            case GLFW_MOUSE_BUTTON_5:
                btn = MouseButton::UP;
                break;

            case GLFW_MOUSE_BUTTON_4:
                btn = MouseButton::DOWN;
                break;
            default:
                std::cout << "Not assigned mouse button code: (" << button << ")" << std::endl;
                return;
            }

            ActionModifier m = static_cast<ActionModifier>(mods);

            if (action == 1)
            {
                auto event = ButtonDownEvent(btn, mods);
                Application::get()->on_event(&event);

            }
            else
            {
                auto event = ButtonUpEvent(btn, mods);
                Application::get()->on_event(&event);
            }
            });

        glfwSetKeyCallback(windowNativePtr, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (action == 1)
            {
                KeyDownEvent event = KeyDownEvent(static_cast<KeyCode>(key), mods);
                Application::get()->on_event(&event);

            }
            else if (action == 0)
            {
                KeyUpEvent event = KeyUpEvent(static_cast<KeyCode>(key), mods);
                Application::get()->on_event(&event);
            }
            });


        return true;
    }

    void Window::swap_buffers()
    {
        glfwSwapBuffers((GLFWwindow*)_window_ptr);   
    }
    void Window::poll_events()
    {
        glfwPollEvents();
    }
    uint32_t Window::get_width() const {
        int width;
        glfwGetWindowSize(static_cast<GLFWwindow*>(_window_ptr), &width, NULL);
        return width;
    }

    uint32_t Window::get_height() const {
        int height;
        glfwGetWindowSize(static_cast<GLFWwindow*>(_window_ptr), NULL, &height);
        return height;
    }

    bool Window::should_close() { return glfwWindowShouldClose((GLFWwindow*)_window_ptr); }
    void Window::make_context_current() { glfwMakeContextCurrent((GLFWwindow*)_window_ptr); }

}
