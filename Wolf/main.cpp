
#include <iostream>

#include "WEngine.h"
#include "Sandbox/OpenGLLayer.h"


int main()
{
	auto app = Wolf::Application();
	app.initialize(Wolf::Window::Configuration());
	Wolf::Layers::ImGuiLayer imguiLayer = Wolf::Layers::ImGuiLayer();
	app.add_layer(&imguiLayer);

	Wolf::SandboxLayers::OpenGLLayer openglLayer = Wolf::SandboxLayers::OpenGLLayer();
	app.add_layer(&openglLayer);

	app.run();
	return 0;
}
