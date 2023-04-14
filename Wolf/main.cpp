
#include <iostream>

#include "WEngine.h"
#include "Sandbox/NBodyLayer.h"


int main()
{
	auto app = Wolf::Application();
	app.initialize(Wolf::Window::Configuration());
	Wolf::Layers::ImGuiLayer imguiLayer = Wolf::Layers::ImGuiLayer();
	app.add_layer(&imguiLayer);

	Wolf::SandboxLayers::NBodyLayer openglLayer = Wolf::SandboxLayers::NBodyLayer();
	app.add_layer(&openglLayer);

	app.run();
	return 0;
}
