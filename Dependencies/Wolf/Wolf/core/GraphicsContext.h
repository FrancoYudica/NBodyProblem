#pragma once
#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H
#include <memory>
#include "Window.h"

namespace Wolf
{
	class  GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual void init() = 0;
		virtual void on_viewport_resize(uint32_t width, uint32_t height) = 0;
		static std::shared_ptr<GraphicsContext> create(const Wolf::Window& window);
	};
}
#endif