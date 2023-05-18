
#include <iostream>

#include "src/MainLayer.h"
#include "Dependencies/WolfEngine/Wolf/WEngine.h"
#include <glm/glm.hpp>

int main()
{

	// REQUIERED CODE
	Wolf::init();
	auto app = Wolf::Application::get();
	bool sucess = app->initialize(Wolf::Window::Configuration());
	if (!sucess)
	{
		std::cout << "Appication init fail" << std::endl;
		return -1;
	}
	;
	app->set_imgui_layer(new Wolf::Layers::ImGuiLayer());
	// END OF REQUIERED CODE

	// CLient layer	
	app->add_layer(new NBody::MainLayer());
	app->run();
	return 0;
}
