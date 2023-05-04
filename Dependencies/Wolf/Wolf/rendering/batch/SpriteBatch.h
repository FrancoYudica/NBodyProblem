#pragma once
#ifndef WOLF_SPRITE_BATCH_H
#define WOLF_SPRITE_BATCH_H

#include "Batch.h"
#include <glm/glm.hpp>

namespace Wolf
{

    namespace Rendering
    {

        struct SpriteVertex
        {
            glm::vec3 position;
            glm::vec4 color;
            glm::vec2 uv;
        };

        class SpriteBatch : public Batch
        {
            public:
            void init(std::shared_ptr<Material>& material) override;    
			void shutdown() override;
			void new_frame() override;
			void end_frame() override;
            void submit_primitive(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
            private:
            void _flush();

            private:
            SpriteVertex* _buffer;


        };
    }

}

#endif