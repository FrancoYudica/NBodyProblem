#include "Window.h"
#include "Application.h"
#include <GLFW/glfw3.h>


namespace Wolf
{

    bool Window::Initialize(Window::Configuration config)
    {
        GLFWmonitor* monitor = config.fullscreen ? glfwGetPrimaryMonitor() : NULL;

        // OpenGL version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* windowNativePtr = glfwCreateWindow(config.width, config.height, config.title, monitor, NULL);

        _windowPtr = windowNativePtr;

        if (!_windowPtr)
        {
            std::cout << "Unable to create GLFWwindow*" << std::endl;
            return false;
        }
        glfwSetWindowUserPointer(windowNativePtr, &_userData);


        // SETS THE EVENT CALLBACKS
        glfwSetCursorPosCallback(windowNativePtr, [](GLFWwindow* window, double x, double y) {
            WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
        MouseMoveEvent event(x, y);
        Application::get_instance()->on_event(event);
            });

        glfwSetWindowCloseCallback(windowNativePtr, [](GLFWwindow* window) {
            WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
        WindowClosedEvent event(userData->windowPtr);
        Application::get_instance()->on_event(event);
            });

        glfwSetWindowSizeCallback(windowNativePtr, [](GLFWwindow* window, int width, int height) {
            WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
        WindowResizeEvent event(width, height);
        Application::get_instance()->on_event(event);
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

            ActionModifier m = (ActionModifier)mods;

            Event buttonEvent;
            if (action == 1)
                buttonEvent = (Event)ButtonDownEvent(btn, mods);
            else
                buttonEvent = (Event)ButtonUpEvent(btn, mods);

            WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
            Application::get_instance()->on_event(buttonEvent);
            });

        glfwSetKeyCallback(windowNativePtr, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

            Event keyEvent;
        if (action == 1)
            keyEvent = (Event)KeyDownEvent((KeyCode)key, mods);
        else if (action == 0)
            keyEvent = (Event)KeyUpEvent((KeyCode)key, mods);
        else
            return;

        WindowUserData* userData = (WindowUserData*)glfwGetWindowUserPointer(window);
        Application::get_instance()->on_event(keyEvent);
            });


        return true;
    }

    bool Wolf::Window::ShouldClose() { return glfwWindowShouldClose((GLFWwindow*)_windowPtr); }
    void Wolf::Window::MakeContextCurrent() { glfwMakeContextCurrent((GLFWwindow*)_windowPtr); }

}
