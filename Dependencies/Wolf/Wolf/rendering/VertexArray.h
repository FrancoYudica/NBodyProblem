
#pragma once
#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include <memory>
#include "Buffer.h"

namespace Wolf
{
	namespace Rendering
	{
		class VertexArray
		{
		public:
			virtual void bind() = 0;
			virtual void unbind() = 0;
			virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb) = 0;
			virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& ib) = 0;
			virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffers() const = 0;
			virtual const std::shared_ptr<IndexBuffer>& get_index_buffer() const = 0;

			static std::shared_ptr<VertexArray> create();
		};

	}
}

#endif