
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
			VertexArray();
			~VertexArray();
			virtual void bind();
			virtual void unbind();
			virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb);
			virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& ib);
			virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffers() const;
			virtual const std::shared_ptr<IndexBuffer> get_index_buffer() const;

		public:
			unsigned int ID;
		private:

			std::shared_ptr<IndexBuffer> _IndexBuffer;
			std::vector<std::shared_ptr<VertexBuffer>> _VertexBuffers;
			unsigned int _AttributeIndex;
		};

	}
}

#endif