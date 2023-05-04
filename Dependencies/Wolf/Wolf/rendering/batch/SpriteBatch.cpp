#include "SpriteBatch.h"
#include "../RenderCommand.h"

using namespace Wolf::Rendering;


void SpriteBatch::init(std::shared_ptr<Material>& material)
{
    Batch::init(material);
    _MAX_SUBMITIONS_CAPACITY = 10000;
    _submitions_count = 0;
    _buffer = new SpriteVertex[_MAX_SUBMITIONS_CAPACITY * 4];

    // The indices are always the same, so i set them once, therefore there is no
	// need for indices allocation
	unsigned int vertices_per_quad = 4;
	unsigned int indices_per_quad = 6;
	unsigned int total_vertices = _MAX_SUBMITIONS_CAPACITY * vertices_per_quad;
	unsigned int indices_count = total_vertices * indices_per_quad;
	unsigned int buffer_size = total_vertices * sizeof(SpriteVertex);
	// Creates the indices array, it's not necessary to re-calculate
	auto indices = new unsigned int[indices_count];
	for (unsigned int quad_index = 0; quad_index < _MAX_SUBMITIONS_CAPACITY; quad_index++)
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
	_vertex_array = VertexArray::create();
	_vertex_array->bind();
	// Creates index and vertex buffer
	_index_buffer = IndexBuffer::create(indices, indices_count);
	delete[] indices;

	_vertex_buffer = VertexBuffer::allocate(buffer_size);

	_vertex_buffer->set_buffer_layout(
		{
			{"Position", ShaderDataType::Float3, false},
			{"Color", ShaderDataType::Float4, false},
			{"UV", ShaderDataType::Float2, false},
		}

	);
	_vertex_array->add_vertex_buffer(_vertex_buffer);
	_vertex_array->set_index_buffer(_index_buffer);

	_vertex_array->unbind();
}

void SpriteBatch::shutdown()
{
    delete[] _buffer;
}
void SpriteBatch::new_frame()
{
    // If not zero, it means we havent flushed
    if (_submitions_count != 0)
    {
        std::cout  << "Error, batch didn't flush" << _submitions_count << std::endl;
        assert(false);
    }
}
void SpriteBatch::end_frame()
{
    if (_submitions_count > 0)
        _flush();
}
void SpriteBatch::_flush()
{
    _material->upload();
	_material->get_shader()->set_matrix("u_view", _camera.get_view());
	_material->get_shader()->set_matrix("u_projection", _camera.get_projection());

    _vertex_array->bind();
    _vertex_buffer->bind(); 
	
    _vertex_buffer->set_sub_data(_buffer, 4 * _submitions_count * sizeof(SpriteVertex), 0);
    RenderCommand::draw_indexed(_vertex_array, _submitions_count * 6, PrimitiveType::Triangles);
    _vertex_array->unbind();
	_vertex_buffer->unbind();
    _submitions_count = 0;
}

void SpriteBatch::submit_primitive(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	unsigned int index = _submitions_count * 4;

	// Sets the array data
	_buffer[index + 0].position = position + glm::vec3(-size.x, -size.y, 0);
	_buffer[index + 1].position = position + glm::vec3( size.x, -size.y, 0);
	_buffer[index + 2].position = position + glm::vec3( size.x,  size.y, 0);
	_buffer[index + 3].position = position + glm::vec3(-size.x,  size.y, 0);
	_buffer[index + 0].color = color;
	_buffer[index + 1].color = color;
	_buffer[index + 2].color = color;
	_buffer[index + 3].color = color;
	_buffer[index + 0].uv = glm::vec2(0, 0);
	_buffer[index + 1].uv = glm::vec2(1, 0);
	_buffer[index + 2].uv = glm::vec2(1, 1);
	_buffer[index + 3].uv = glm::vec2(0, 1);

	if (++_submitions_count == _MAX_SUBMITIONS_CAPACITY)
		_flush();
}