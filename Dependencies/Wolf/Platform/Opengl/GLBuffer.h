#pragma once
#ifndef GL_BUFFER_H
#define GL_BUFFER_H

#include "rendering/Buffer.h"

using namespace Wolf::Rendering;

namespace Wolf
{
	namespace Rendering
	{

		namespace GL
		{
			class GLVertexBuffer : public VertexBuffer
			{
			public:

				unsigned int ID;
				GLVertexBuffer(const GLVertexBuffer& other) = delete;
				GLVertexBuffer(const void* vertices, unsigned int size);
				GLVertexBuffer(unsigned int size);

				virtual ~GLVertexBuffer();
				virtual void bind() const;
				virtual void unbind() const;
				virtual void set_sub_data(const void* data, unsigned int size, unsigned int offset);
				virtual void set_buffer_layout(const BufferLayout& layout) { _Layout = layout; }
				virtual BufferLayout& get_buffer_layout() { return _Layout; }

			private:
				BufferLayout _Layout;

			};


			class GLIndexBuffer : public IndexBuffer
			{
			public:
				unsigned int ID;
				GLIndexBuffer(const GLIndexBuffer& other) = delete;
				GLIndexBuffer(const unsigned int* indices, unsigned int count);
				virtual ~GLIndexBuffer();
				virtual void bind() const;
				virtual void unbind() const;
				virtual void set_sub_data(const void* data, unsigned int size, unsigned int offset);
				virtual unsigned int get_count() const { return _Count; }

			private:
				unsigned int _Count;
			};
		}
	}
}

#endif