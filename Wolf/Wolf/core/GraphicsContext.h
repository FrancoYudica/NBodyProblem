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
		GraphicsContext(const Window& window) 
		: _glfwWindow(window.GetNativePtr()) {}
		virtual void Init();
		virtual void SwapBuffers();

	private:
		void* _glfwWindow;
	};
}
#endif