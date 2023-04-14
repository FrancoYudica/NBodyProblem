#include "Renderer.h"
#include <memory>
#include "../WEngine.h"

#include <glad/glad.h>
using namespace Wolf::Rendering;


const char* vertexShaderSourceStr = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"out vec4 _Color;\n"
"void main()\n"
"{\n"
"	_Color = aColor;\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSourceStr = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 _Color;\n"
"void main()\n"
"{\n"
"   FragColor = _Color;\n"
"}\n\0";


struct QuadVertex
{
	glm::vec3 position;
	glm::vec4 color;
};

struct RendererData
{
	unsigned int MaxQuads; // Max amount of Quads, (4 QuadVertex per quad)
	unsigned int Submitions;
	std::shared_ptr<VertexArray> VAO;
	std::shared_ptr<VertexBuffer> VBO;
	std::shared_ptr<IndexBuffer> IBO;
	std::shared_ptr<ShaderProgram> ShaderProgram;
	QuadVertex* VerticesPtr;
	
};

// Data used for the renderer
static RendererData _Data;


void Renderer2D::Init()
{
	_Data.MaxQuads = 100;
	_Data.Submitions = 0;
	_Data.VerticesPtr = new QuadVertex[_Data.MaxQuads * 4];

	// The indices are always the same, so i set them once, therefore there is no
	// need for indices allocation
	unsigned int vertices_per_quad = 4;
	unsigned int indices_per_quad = 6;
	unsigned int total_vertices = _Data.MaxQuads * vertices_per_quad;
	unsigned int indices_count = total_vertices * indices_per_quad;
	unsigned int buffer_size = total_vertices * sizeof(QuadVertex);
	// Creates the indices array, it's not necessary to re-calculate
	auto indices = new unsigned int[indices_count];
	for (unsigned int quad_index = 0; quad_index < _Data.MaxQuads; quad_index++)
	{
		unsigned int index = 		quad_index * indices_per_quad;
		unsigned int vertex_index = quad_index * vertices_per_quad;
		indices[index + 0] = vertex_index + 0;
		indices[index + 1] = vertex_index + 1;
		indices[index + 2] = vertex_index + 2;
		indices[index + 3] = vertex_index + 0;
		indices[index + 4] = vertex_index + 2;
		indices[index + 5] = vertex_index + 3;
	}

	// Creates VAO, IBO and VBO
	_Data.VAO = std::make_shared<VertexArray>();
	_Data.VAO->bind();
	// Creates index and vertex buffer
	_Data.IBO = std::make_shared<IndexBuffer>(indices, indices_count);
	delete[] indices;

	_Data.VBO = std::make_shared<VertexBuffer>(_Data.VerticesPtr, buffer_size);

	_Data.VBO->set_buffer_layout(
		BufferLayout{
			BufferAttribute("Position", ShaderDataType::Float3, false),
			BufferAttribute("Color", ShaderDataType::Float4, false)
			}
	);
	_Data.VAO->add_vertex_buffer(_Data.VBO);
	_Data.VAO->set_index_buffer(_Data.IBO);

	_Data.VAO->unbind();
	_Data.ShaderProgram = std::make_shared<ShaderProgram>(vertexShaderSourceStr, fragmentShaderSourceStr);
}

void Renderer2D::Shutdown()
{
	// Deallocates the memory
	delete[] _Data.VerticesPtr;
}

void Renderer2D::NewFrame()
{
	if (_Data.Submitions != 0)
	{
		assert(false);
	}
	_Data.Submitions = 0;
}

void Renderer2D::EndFrame()
{
	if (_Data.Submitions == 0)
		return;

	_Flush();
}

void Renderer2D::SubmitQuad(const glm::vec3& position, const glm::vec3 size, const glm::vec4& color)
{
	unsigned int index = _Data.Submitions * 4;

	_Data.VerticesPtr[index + 0].position = position + glm::vec3(-size.x, -size.y, 0);
	_Data.VerticesPtr[index + 1].position = position + glm::vec3( size.x, -size.y, 0);
	_Data.VerticesPtr[index + 2].position = position + glm::vec3( size.x,  size.y, 0);
	_Data.VerticesPtr[index + 3].position = position + glm::vec3(-size.x,  size.y, 0);

	_Data.VerticesPtr[index + 0].color = color;
	_Data.VerticesPtr[index + 1].color = color;
	_Data.VerticesPtr[index + 2].color = color;
	_Data.VerticesPtr[index + 3].color = color;


	_Data.Submitions++;

	if (_Data.Submitions > _Data.MaxQuads)
		_Flush();

}

void Renderer2D::_Flush()
{

	// Renders the batched quads
	_Data.ShaderProgram->bind();
	_Data.VAO->bind();
	_Data.VBO->bind();
	_Data.VBO->set_sub_data(_Data.VerticesPtr, 4 * _Data.Submitions * sizeof(QuadVertex), 0);
	Wolf::Rendering::RenderCommand::DrawIndexed(_Data.VAO, _Data.Submitions * 6);
	_Data.VAO->unbind();

	// Rests
	_Data.Submitions = 0;
}
