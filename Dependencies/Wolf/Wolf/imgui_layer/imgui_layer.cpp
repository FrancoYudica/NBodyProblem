
#include "imgui_layer.h"
#include <iostream>
#include "../core/Application.h"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"



namespace Wolf
{
	namespace Layers
	{
		void ImGuiLayer::on_start()
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); 
			ImGui::StyleColorsDark();
			Application* instance = Application::get();
			Window* window = instance->get_main_window();
			ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->get_native_ptr(), true);
			ImGui_ImplOpenGL3_Init("#version 330");	
		}

		void ImGuiLayer::on_end()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		void ImGuiLayer::on_update(const Time& delta)
		{
			
		}

		void ImGuiLayer::on_render()
		{

		}

		void ImGuiLayer::on_event(Event* event)
		{
			EventDispatcher dispatcher(event);
			dispatcher.dispatch<Event>(EventType::ButtonDown, [](Event* e) { std::cout << "Button pressed" << std::endl; return false; });
		}
		void ImGuiLayer::on_ui_render_start()
		{
			// Tell OpenGL a new frame is about to begin
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void ImGuiLayer::on_ui_render_finish()
		{
			// Renders the ImGUI elements
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

	}
}
