#include "Time.h"
#include <GLFW/glfw3.h>

namespace Wolf
{
    Time Time::current()
    {
        return Time(glfwGetTime());
    }

    std::ostream& operator << (std::ostream& stream, const Time& time)
    {
        stream << time.seconds();
        return stream;
    }
}
