
#include "RenderCommand.h"
#include <glad/glad.h>


using namespace Wolf::Rendering;

void RenderCommand::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
void RenderCommand::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vao, int count)
{
    vao->get_index_buffer()->bind();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

