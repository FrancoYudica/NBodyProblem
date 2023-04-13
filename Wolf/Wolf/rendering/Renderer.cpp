#include "Renderer.h"


using namespace Wolf::Rendering;

RendererData Renderer2D::_Data;


void Renderer2D::Init()
{
	_Data.BatchSize = 10000;
	
	//_vertex_array = Wolf::Rendering::VertexArray::Create();
	
	// The indices are always the same, so i set them once
	unsigned int vertices_per_quad = 4;
	unsigned int indices_per_quad = 6;
	unsigned int total_vertices = _Data.BatchSize * vertices_per_quad;
	unsigned int indices_count = total_vertices * indices_per_quad;
	auto indices = new unsigned int[indices_count];
	
	for (unsigned int quad_index = 0; quad_index < _Data.BatchSize; quad_index++)
	{
		unsigned int index = quad_index * vertices_per_quad * indices_per_quad;
		indices[index] = index;
		indices[index + 1] = index + 1;
		indices[index + 2] = index + 2;
	
		indices[index + 3] = index;
		indices[index + 4] = index + 2;
		indices[index + 5] = index + 3;
	}
	_Data.Submitions = 0;

	_Data.VAO = std::make_shared<VertexArray>();
	_Data.VAO->bind();
	_Data.IBO = std::make_shared<IndexBuffer>(indices, indices_count);
	_Data.Vertices.resize(_Data.BatchSize);
	_Data.VBO = std::make_shared<VertexBuffer>(&_Data.Vertices[0], _Data.BatchSize * sizeof(QuadVertex));
	_Data.VAO->unbind();
}

void Wolf::Rendering::Renderer2D::NewFrame()
{
	_Data.Submitions = 0;
}

void Wolf::Rendering::Renderer2D::EndFrame()
{

}

void Wolf::Rendering::Renderer2D::SubmitQuad(const glm::vec3& position, const glm::vec3 size, const glm::vec4& color)
{
	unsigned int index = _Data.Submitions * 4;

	QuadVertex v0 = { position + glm::vec3(-size.x, -size.y, 0), color, glm::vec2(0), 0 };
	QuadVertex v1 = { position + glm::vec3(+size.x, -size.y, 0), color, glm::vec2(0), 0 };
	QuadVertex v2 = { position + glm::vec3(+size.x, +size.y, 0), color, glm::vec2(0), 0 };
	QuadVertex v3 = { position + glm::vec3(-size.x, +size.y, 0), color, glm::vec2(0), 0 };

	_Data.Vertices[index] = v0;
	_Data.Vertices[index + 1] = v1;
	_Data.Vertices[index + 2] = v2;
	_Data.Vertices[index + 3] = v3;

	_Data.Submitions++;

}

void Wolf::Rendering::Renderer2D::_Flush()
{
	_Data.VAO->bind();

	_Data.VAO->unbind();
}
