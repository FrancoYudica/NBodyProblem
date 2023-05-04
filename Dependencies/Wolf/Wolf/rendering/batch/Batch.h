#pragma once
#ifndef WOLF_BATCH_H
#define WOLF_BATCH_H

#include <glm/glm.hpp>
#include "../VertexArray.h"
#include "../Buffer.h"
#include "../Material.h"
#include "../Camera.h"

namespace Wolf
{

    namespace Rendering
    {
        class Batch
        {
            public:
            
            virtual void init(std::shared_ptr<Material>& material) 
            {
                _material = material;
            }    
            virtual void begin_scene(const Camera& camera) { _camera = camera; }
			virtual void shutdown() {}
			virtual void new_frame() {}
			virtual void end_frame() {}

            protected:
            std::shared_ptr<VertexArray> _vertex_array;
            std::shared_ptr<VertexBuffer> _vertex_buffer;
            std::shared_ptr<IndexBuffer> _index_buffer;
            std::shared_ptr<Material> _material;
            uint32_t _submitions_count;
            uint32_t _MAX_SUBMITIONS_CAPACITY;
            Camera _camera;
        };
    }

}

#endif