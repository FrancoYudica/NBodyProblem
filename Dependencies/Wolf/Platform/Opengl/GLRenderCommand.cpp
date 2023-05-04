#include <glad/glad.h>
#include "../WEngine.h"

using namespace Wolf::Rendering;


// Links the definitions for the render commands
void RenderCommand::set_clear_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void RenderCommand::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);   
}

void RenderCommand::draw_indexed(const std::shared_ptr<VertexArray>& vao, int count, PrimitiveType primitive)
{
    auto ibo = vao->get_index_buffer();
    ibo->bind();

    switch (primitive)
    {
    case PrimitiveType::Triangles:
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
        break;

    case PrimitiveType::Lines:
        glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, 0);
        break;

    default:
        std::cout << "RenderCommand::draw_indexed inimplemented primitive type: " << primitive << std::endl;
        break;
    }
}

void RenderCommand::draw_arrays(const std::shared_ptr<VertexArray>& vao, uint32_t count, PrimitiveType primitive)
{
    switch (primitive)
    {
    case PrimitiveType::TriangleStrip:
        glDrawArrays(GL_TRIANGLE_STRIP, 0, count);
        break;

    default:
        std::cout << "RenderCommand::draw_arrays inimplemented primitive type: " << primitive << std::endl;
        break;
    }
}
void RenderCommand::set_blending_mode(BlendMode mode)
{
    switch (mode)
    {
    case BlendMode::Transparent:
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        break;
    
    default:
        std::cout << "Unimplemented blend mode: " << mode << std::endl;
        break;
    }

}