#pragma once
#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include "core/GraphicsContext.h"
namespace Wolf
{
    namespace Rendering
    {
    namespace GL
        {
            class GLGraphicsContext : public GraphicsContext
            {
            public:
            	GLGraphicsContext() = default;
                GLGraphicsContext(void* glfwWindow) : _glfwWindow(glfwWindow) {}

            	virtual void init();
        		void on_viewport_resize(uint32_t width, uint32_t height);

            private:
                    void* _glfwWindow;
            };
            
        }
    }
}
#endif