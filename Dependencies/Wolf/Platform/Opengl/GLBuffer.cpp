#include "GLBuffer.h"
#include <glad/glad.h>

using namespace Wolf::Rendering;
using namespace Wolf::Rendering::GL;

// VERTEX_BUFFER
GLVertexBuffer::GLVertexBuffer(const void* vertices, unsigned int size)
{
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLVertexBuffer::GLVertexBuffer(unsigned int size)
{
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void GLVertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void GLVertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void GLVertexBuffer::set_sub_data(const void* data, unsigned int size, unsigned int offset)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

// INDEX_BUFFER
GLIndexBuffer::GLIndexBuffer(const unsigned int* indices, unsigned int count)
{
	_Count = count;
	// Generates the buffer as an array buffer
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

	// Sets the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLIndexBuffer::~GLIndexBuffer()
{
	glDeleteBuffers(1, &ID);
}

void GLIndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void GLIndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLIndexBuffer::set_sub_data(const void* data, unsigned int size, unsigned int offset)
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}


// Definitions for VertexBuffer::Create and IndexBuffer::Create
// Links the definitions of all the other RENDERING Static functions
std::shared_ptr<VertexBuffer> VertexBuffer::create(const void* data, unsigned int size)
{
    // Size is the amount of bytes of the array
    return std::make_shared<GLVertexBuffer>(data, size);
}

std::shared_ptr<VertexBuffer> VertexBuffer::allocate(unsigned int size)
{
    return std::make_shared<GLVertexBuffer>(size);
}

std::shared_ptr<IndexBuffer> IndexBuffer::create(const unsigned int* data, unsigned int count)
{
    // Count is the length of the array
    return std::make_shared<GLIndexBuffer>(data, count);
}
