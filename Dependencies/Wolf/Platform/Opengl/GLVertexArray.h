#pragma once
#ifndef GL_VERTEX_ARRAY_H
#define GL_VERTEX_ARRAY_H

#include "rendering/VertexArray.h"


namespace Wolf
{
	namespace Rendering
	{
		namespace GL
		{ 
			class GLVertexArray : public VertexArray
			{
			public:
				unsigned int ID;
				GLVertexArray();
				~GLVertexArray();
				virtual void bind();
				virtual void unbind();
				virtual void add_vertex_buffer(const std::shared_ptr<VertexBuffer>& vb);
				virtual void set_index_buffer(const std::shared_ptr<IndexBuffer>& ib);
				virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffers() const { return _VertexBuffers; }
				virtual const std::shared_ptr<IndexBuffer>& get_index_buffer() const { return _IndexBuffer; }
			private:

				std::shared_ptr<IndexBuffer> _IndexBuffer;
				std::vector<std::shared_ptr<VertexBuffer>> _VertexBuffers;
				unsigned int _AttributeIndex;
			};
		}
	}
}


#endif