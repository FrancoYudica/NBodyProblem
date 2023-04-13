#include "Time.h"
#include <GLFW/glfw3.h>

namespace Wolf
{
    Time Time::current()
    {
        return Time(glfwGetTime());
    }
}
