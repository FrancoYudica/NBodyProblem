#include "OpenGLContext.h"
#include "GLBuffer.h"
#include "GLShaderProgram.h"
#include "GLVertexArray.h"
#include <memory>
#include <glad/glad.h>
#include "core/Window.h"
#include "rendering/RenderCommand.h"
#include <GLFW/glfw3.h>


using namespace Wolf;
using namespace Wolf::Rendering;
using namespace Wolf::Rendering::GL;

// GRAPHICS CONTEXT
std::shared_ptr<GraphicsContext> GraphicsContext::create(const Wolf::Window& window)
{
    return std::make_shared<GLGraphicsContext>(window.get_native_ptr());
}

void GLGraphicsContext::init()
{
    int sucess = gladLoadGL();
    if (sucess == 0)
        std::cout << "Unable to load glad" << std::endl;
}

void GLGraphicsContext::on_viewport_resize(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}
