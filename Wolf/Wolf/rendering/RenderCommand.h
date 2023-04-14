#pragma once
#ifndef WOLF_RENDER_COMMAND_H
#define WOLF_RENDER_COMMAND_H
#include <memory>
#include "VertexArray.h"
#include "Buffer.h"


namespace Wolf
{
    namespace Rendering
    {

        class RenderCommand
        {
            public:
                static void SetClearColor(float r, float g, float b, float a);
                static void Clear();
                static void DrawIndexed(const std::shared_ptr<VertexArray>& vao, int count);
        };

    }
}


#endif