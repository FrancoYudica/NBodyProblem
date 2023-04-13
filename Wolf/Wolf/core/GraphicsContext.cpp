#include "GraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace Wolf;

void GraphicsContext::Init()
{
    int sucess = gladLoadGL();
    if (sucess == 0)
        std::cout << "Unable to load glad" << std::endl;
}


void GraphicsContext::SwapBuffers()
{
    glfwSwapBuffers((GLFWwindow*)_glfwWindow);
}
