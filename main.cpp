
#include <iostream>

#include "src/MainLayer.h"
#include "Dependencies/Wolf/WEngine.h"
#include <glm/glm.hpp>

int main()
{
	Wolf::init();
	auto app = Wolf::Application::get();
	bool sucess = app->initialize(Wolf::Window::Configuration());
	if (!sucess)
	{
		std::cout << "Appication init fail" << std::endl;
		return -1;
	}

	// If imgui is used
	Wolf::Layers::ImGuiLayer imguiLayer = Wolf::Layers::ImGuiLayer();
	app->add_layer(&imguiLayer);
	
	// CLient layer	
	NBody::MainLayer layer;
	app->add_layer(&layer);
	app->run();
	return 0;
}
