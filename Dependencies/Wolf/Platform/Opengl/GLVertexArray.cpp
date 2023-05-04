#include "GLVertexArray.h"
#include <glad/glad.h>

using namespace Wolf::Rendering::GL;
using namespace Wolf::Rendering;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat2:     return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		default:
			std::cout << "Unimplememted shader data type to GL base type: " << type << std::endl;
	}
	return 1;

}

GLVertexArray::GLVertexArray()
{
	ID = 0;
	glGenVertexArrays(1, &ID);
	_AttributeIndex = 0;
}

GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &ID);
}

void GLVertexArray::bind()
{
	glBindVertexArray(ID);
}

void GLVertexArray::unbind()
{
	glBindVertexArray(0);
}

void GLVertexArray::add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb)
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
			ShaderDataTypeToOpenGLBaseType(attribute.type),
			attribute.normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(uint32_t*)attribute.offset
		);
		_AttributeIndex++;
	}
}

void GLVertexArray::set_index_buffer(const std::shared_ptr<IndexBuffer>& ib)
{
	bind();
	ib->bind();
	_IndexBuffer = ib;

}

std::shared_ptr<VertexArray> VertexArray::create()
{
    return std::make_shared<GLVertexArray>();
}
