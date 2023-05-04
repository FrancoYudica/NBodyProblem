#include "LineBatch.h"
#include "../RenderCommand.h"

using namespace Wolf::Rendering;


void LineBatch::init(std::shared_ptr<Material>& material)
{
    
    Batch::init(material);
    _MAX_SUBMITIONS_CAPACITY = 10000;
    _submitions_count = 0;

	unsigned int vertices_per_primitive = 6;
    _buffer = new LineVertex[_MAX_SUBMITIONS_CAPACITY * vertices_per_primitive];

    // The indices are always the same, so i set them once, therefore there is no
	// need for indices allocation
	unsigned int indices_per_primitive = 12;
	unsigned int total_vertices = _MAX_SUBMITIONS_CAPACITY * vertices_per_primitive;
	unsigned int indices_count = total_vertices * indices_per_primitive;
	unsigned int buffer_size = total_vertices * sizeof(LineVertex);
	// Creates the indices array, it's not necessary to re-calculate
	auto indices = new unsigned int[indices_count];
	for (unsigned int quad_index = 0; quad_index < _MAX_SUBMITIONS_CAPACITY; quad_index++)
	{
		unsigned int index = 		quad_index * indices_per_primitive;
		unsigned int vertex_index = quad_index * vertices_per_primitive;
		indices[index + 0] = vertex_index + 0;
		indices[index + 1] = vertex_index + 1;
		indices[index + 2] = vertex_index + 4;

		indices[index + 3] = vertex_index + 0;
		indices[index + 4] = vertex_index + 4;
		indices[index + 5] = vertex_index + 3;

        indices[index + 6] = vertex_index + 1;
		indices[index + 7] = vertex_index + 2;
		indices[index + 8] = vertex_index + 5;

		indices[index + 9] = vertex_index + 1;
		indices[index + 10] = vertex_index + 5;
		indices[index + 11] = vertex_index + 4;
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
			{"Color", ShaderDataType::Float4, false}
		}

	);
	_vertex_array->add_vertex_buffer(_vertex_buffer);
	_vertex_array->set_index_buffer(_index_buffer);

	_vertex_array->unbind();
}

void LineBatch::shutdown()
{
    delete[] _buffer;
}
void LineBatch::new_frame()
{
    // If not zero, it means we havent flushed
    if (_submitions_count != 0)
    {
        std::cout  << "Error, batch didn't flush" << _submitions_count << std::endl;
        assert(false);
    }
}
void LineBatch::end_frame()
{
    if (_submitions_count > 0)
        _flush();
}
void LineBatch::_flush()
{
    RenderCommand::set_blending_mode(BlendMode::Transparent);
    _material->upload();
	_material->get_shader()->set_matrix("u_view", _camera.get_view());
	_material->get_shader()->set_matrix("u_projection", _camera.get_projection());

    _vertex_array->bind();
    _vertex_buffer->bind(); 
	
    _vertex_buffer->set_sub_data(_buffer, 6 * _submitions_count * sizeof(LineVertex), 0);
    RenderCommand::draw_indexed(_vertex_array, _submitions_count * 12, PrimitiveType::Triangles);
    _vertex_array->unbind();
	_vertex_buffer->unbind();
    _submitions_count = 0;
}

void LineBatch::submit_primitive(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, const float thickness)
{   
    auto diff = p1 - p0;
    float angle = std::atan2(diff.y, diff.x);
 
    float x_displacement = 0.5f * thickness * std::sin(-angle);
    float y_displacement = 0.5f * thickness * std::cos(-angle);

	unsigned int index = _submitions_count * 6;
    float half_thickness = thickness * 0.5f;
	// Sets the array data
	_buffer[index + 0].position = p0 + glm::vec3(-x_displacement, -y_displacement, 0);
	_buffer[index + 1].position = p0;
	_buffer[index + 2].position = p0 + glm::vec3(x_displacement, y_displacement, 0);

	_buffer[index + 3].position = p1 + glm::vec3(-x_displacement, -y_displacement, 0);
	_buffer[index + 4].position = p1;
	_buffer[index + 5].position = p1 + glm::vec3(x_displacement, y_displacement, 0);

   	_buffer[index + 0].color = color;
	_buffer[index + 1].color = color;
	_buffer[index + 2].color = color;
	_buffer[index + 3].color = color;
	_buffer[index + 4].color = color;
    _buffer[index + 5].color = color;
	if (++_submitions_count == _MAX_SUBMITIONS_CAPACITY)
		_flush();
}

void LineBatch::submit_primitive_interpolated(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, const float thickness)
{   
    auto diff = p1 - p0;
    float angle = std::atan2(diff.y, diff.x);

    float x_displacement = 0.5f * thickness * std::sin(-angle);
    float y_displacement = 0.5f * thickness * std::cos(-angle);

	unsigned int index = _submitions_count * 6;
    float half_thickness = thickness * 0.5f;
	// Sets the array data
	_buffer[index + 0].position = p0 + glm::vec3(-x_displacement, -y_displacement, 0);
	_buffer[index + 1].position = p0;
	_buffer[index + 2].position = p0 + glm::vec3(x_displacement, y_displacement, 0);

	_buffer[index + 3].position = p1 + glm::vec3(-x_displacement, -y_displacement, 0);
	_buffer[index + 4].position = p1;
	_buffer[index + 5].position = p1 + glm::vec3(x_displacement, y_displacement, 0);

    _buffer[index + 0].color = glm::vec4(0);
    _buffer[index + 1].color = color;
    _buffer[index + 2].color = glm::vec4(0);
    _buffer[index + 3].color = glm::vec4(0);
    _buffer[index + 4].color = color;
    _buffer[index + 5].color = glm::vec4(0);

	if (++_submitions_count == _MAX_SUBMITIONS_CAPACITY)
		_flush();
}