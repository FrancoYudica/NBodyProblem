#include "VertexArray.h"
#include <glad/glad.h>
#include <iostream>

using namespace Wolf::Rendering;

static GLenum ShaderDataTypeToOpenGLBaseType(Wolf::Rendering::ShaderDataType type)
{
	switch (type)
	{
		case Wolf::Rendering::ShaderDataType::Float:    return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Float2:   return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Float3:   return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Float4:   return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Mat2:     return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Mat3:     return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Mat4:     return GL_FLOAT;
		case Wolf::Rendering::ShaderDataType::Int:      return GL_INT;
		case Wolf::Rendering::ShaderDataType::Int2:     return GL_INT;
		case Wolf::Rendering::ShaderDataType::Int3:     return GL_INT;
		case Wolf::Rendering::ShaderDataType::Int4:     return GL_INT;
		default:
			std::cout << "Unimplememted shader data type to GL base type: " << type << std::endl;
	}
	return 1;

}

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
	_AttributeIndex = 0;
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void VertexArray::bind()
{
	glBindVertexArray(ID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb)
{
	_VertexBuffers.push_back(vb);
	bind();
	vb->bind();
	BufferLayout layout = vb->get_buffer_layout();

	for (BufferAttribute& attribute : layout)
	{
		glEnableVertexAttribArray(_AttributeIndex);
		glVertexAttribPointer(
			_AttributeIndex,
			attribute.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(attribute.Type),
			attribute.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(void*)attribute.Offset
		);
		_AttributeIndex++;
	}
}

void VertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& ib)
{
	bind();
	ib->bind();
	_IndexBuffer = ib;

}

const std::vector<std::shared_ptr<VertexBuffer>>& VertexArray::get_vertex_buffers() const
{
    return _VertexBuffers;
}

const std::shared_ptr<IndexBuffer> VertexArray::get_index_buffer() const
{
    return _IndexBuffer;
}

