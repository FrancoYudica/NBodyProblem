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

        enum BlendMode {Transparent};
        enum PrimitiveType {Triangles, TriangleStrip, Lines};
        class RenderCommand
        {
            public:
                static void set_clear_color(float r, float g, float b, float a);
                static void clear();
                static void draw_indexed(const std::shared_ptr<VertexArray>& vao, int count, PrimitiveType primitive);
                static void draw_arrays(const std::shared_ptr<VertexArray>& vao, uint32_t count, PrimitiveType primitive);
                static void set_blending_mode(BlendMode mode);
        };

    }
}


#endif