
#include "Buffer.h"
#include <glad/glad.h>


using namespace Wolf::Rendering;
// VERTEX_BUFFER
VertexBuffer::VertexBuffer(const void* vertices, unsigned int size)
{
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::VertexBuffer(unsigned int size)
{
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void VertexBuffer::set_sub_data(const void* data, unsigned int size, unsigned int offset)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::set_buffer_layout(const BufferLayout& layout)
{
    _Layout = layout;
}

BufferLayout& VertexBuffer::get_buffer_layout() {
    return _Layout;
}


// INDEX_BUFFER
IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count)
{
	_Count = count;
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::set_sub_data(const void* data, unsigned int size, unsigned int offset)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

