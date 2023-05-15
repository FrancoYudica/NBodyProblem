
#include "MainLayer.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <glm/gtx/string_cast.hpp>
#include <queue>
#include <execution>


namespace NBody
{
	void MainLayer::on_start()
	{
		Rendering::Renderer2D::init();
		Window* window = Application::get()->get_main_window();
		_camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);
		_debug_camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);
		_debug_render = false;
		_simulation_speed = 1.0f;
		_simulation = std::make_unique<BarnesHutSimulation>();
		_reset_simulation();
	}
	void MainLayer::on_event(Event* event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowResizeEvent>(
			EventType::WindowResize,
			[this](WindowResizeEvent* resize_event){
				_camera.on_viewport_resize(resize_event->width, resize_event->height);
				_debug_camera.on_viewport_resize(resize_event->width, resize_event->height);
				return false;
			}
		);
		dispatcher.dispatch<MouseScrollEvent>(
			EventType::MouseScroll,
			[this](MouseScrollEvent* scroll)
			{
				float zoom_ratio = 0.25f;
				float zoom = _camera.get_zoom();
				float offset = _camera.get_zoom() * zoom_ratio * scroll->y_offset;
				_camera.set_zoom(zoom + offset);
				return false;
			}
		);

		dispatcher.dispatch<ButtonDownEvent>(
			EventType::ButtonDown,
			[this](ButtonDownEvent* event)
			{
				_clicked_position = Input::get_mouse_pos();
				return false;
			}
		);

		dispatcher.dispatch<ButtonUpEvent>(
			EventType::ButtonUp,
			[this](ButtonUpEvent* event)
			{
				auto pos = Wolf::Input::get_mouse_pos();
				glm::vec2 direction = pos - _clicked_position;
				glm::vec2 position = Wolf::Input::screen_to_world_coord(_camera, pos);
				_simulation->add_body(position, -direction, 20);
				return false;
			}
		);
	}
	void MainLayer::on_update(const Time& delta)
	{
		// Updates camera translation
		float speed = 2.0f * delta.seconds() / _camera.get_zoom();
		glm::vec3 direction(0);
		if (Wolf::Input::is_key_down(KeyCode::KEY_W))
			direction += glm::vec3(0, 1, 0);
		if (Wolf::Input::is_key_down(KeyCode::KEY_S))
			direction += glm::vec3(0, -1, 0);
		if (Wolf::Input::is_key_down(KeyCode::KEY_D))
			direction += glm::vec3(1, 0, 0);
		if (Wolf::Input::is_key_down(KeyCode::KEY_A))
			direction += glm::vec3(-1, 0, 0);

		_camera.set_position(_camera.get_position() + direction * speed);

		float step = 1.0f / 200.0f * _simulation_speed;
		float smoothing = 0.001;
		float g = 6e-5;
		_simulation->update(g, smoothing, step);

		/*
		for (Body& body : _bodies)
			_tree_clean->attract(&body, delta_seconds);

		uint32_t index = 0;

		while(index < _bodies.size())
		{
			Body& body = _bodies[index];
			if (!body.tree->translate(&body, 1.0f / 200.0f))
			{
				_bodies.erase(_bodies.begin() + index);
			}
			else
			{
				index++;
			}
		}
		*/

		
	}
	void MainLayer::on_ui_render_start()
	{
		ImGui::Begin("Status");
		float render_time = Application::get()->get_render_time().seconds();
		float update_time = Application::get()->get_update_time().seconds();
		ImGui::Text(("Render time: " + std::to_string(render_time)).c_str());
		ImGui::Text(("Update time: " + std::to_string(update_time)).c_str());
		ImGui::End();

		ImGui::Begin("Simulation");
		std::string body_count_text = "Body count: " + std::to_string(_simulation->body_count());
		ImGui::Text(body_count_text.c_str());
		
		ImGui::Checkbox("Debug render", &_debug_render);

		ImGui::DragFloat("Simulation speed", &_simulation_speed, 0.05f, 0.1f, 3.0f);

		if (ImGui::Button("Reset simulation"))
			_reset_simulation();

		if(ImGui::Button("Clear"))
			_simulation->clear();

		ImGui::End();
	}
	void MainLayer::on_ui_render_finish()
	{
	}
	void MainLayer::on_end()
	{
	}
	void MainLayer::on_render()
	{
		
		if (_debug_render)
			_simulation->debug_render(_camera);

		_simulation->render(_camera);

		// Debug rendering
		Rendering::Renderer2D::begin_scene(_debug_camera);
		Rendering::Renderer2D::new_frame();
		// Simulation boundary rectangle
		glm::vec4 boundary_color = {1, 1, 1, 1};
		float thickness = 0.01;
		float half_size = _simulation_size * 0.5f;
		glm::vec2 bottom_left =   Input::world_to_screem_coord(_camera, {-half_size, -half_size});
		glm::vec2 bottom_right = Input::world_to_screem_coord(_camera, {half_size, -half_size});
		glm::vec2 top_right = Input::world_to_screem_coord(_camera,  {half_size, half_size});
		glm::vec2 top_left = Input::world_to_screem_coord(_camera, {-half_size, half_size});
		Rendering::Renderer2D::submit_line(bottom_left, bottom_right, boundary_color, thickness);
		Rendering::Renderer2D::submit_line(bottom_left, top_left, boundary_color, thickness);
		Rendering::Renderer2D::submit_line(top_left, top_right, boundary_color, thickness);
		Rendering::Renderer2D::submit_line(bottom_right, top_right, boundary_color, thickness);

		if (Input::is_button_down(MouseButton::LEFT))
		{
			glm::vec2 pos = Input::get_mouse_pos();
			Rendering::Renderer2D::submit_line(pos, _clicked_position, {1, 0, 0, 1}, 0.01f);
		}

		Rendering::Renderer2D::end_frame();
	}

	void MainLayer::_reset_simulation()
	{
		//_bodies.clear();
		uint32_t start_body_count = 30;
		_simulation_size = 1;

		_simulation->clear();
		_simulation->init(start_body_count, _simulation_size);
		float smoothing = 0.001;
		float g = 6e-5;
		uint32_t size = static_cast<uint32_t>(sqrt(start_body_count));
		float step = static_cast<float>(_simulation_size) / static_cast<float>(size);
		for (uint32_t i = 1; i < size; i++)
		{
			float x = step * i - _simulation_size * 0.5f;			
			for (uint32_t j = 1; j < size; j++)
			{
				float y = step * j - _simulation_size * 0.5f;
				float mass = Wolf::Numerical::Random::range_f(15.0f, 30.0f);
				_simulation->add_body({x, y}, {0, 0}, mass);
			}
		}

		// Inserts all the objects into the tree for the first time
		//for (Body& body : _bodies)
		//	_tree_clean->insert(&body);

		/*

		for (uint32_t i = 0; i < 200; i++)
		{
			float x = Wolf::Numerical::Random::range_f(-2, -.5f);
			float y = Wolf::Numerical::Random::range_f(-1, 0.4);

			float x_vel = Wolf::Numerical::Random::range_f(0, 0);
			float y_vel = Wolf::Numerical::Random::range_f(0, .5);
			float mass = Wolf::Numerical::Random::range_f(5.0f, 15.0f);
			_bodies.push_back(Body{{x, y}, {x_vel, y_vel}, mass});
		}

		for (uint32_t i = 0; i < 200; i++)
		{
			float x = Wolf::Numerical::Random::range_f(0.5, 2);
			float y = Wolf::Numerical::Random::range_f(-1, 0.4);

			float x_vel = Wolf::Numerical::Random::range_f(0, 0);
			float y_vel = Wolf::Numerical::Random::range_f(0, -.5);
			float mass = Wolf::Numerical::Random::range_f(5.0f, 15.0f);
			Body body = Body{{x, y}, {x_vel, y_vel}, mass};
			_bodies.push_back(body);
		}


		glm::vec2 center(0.0f, 0.0f);

		for (uint32_t i = 0; i < 500; i++)
		{
			
			float x, y, distance;
			distance = 0;
			while (distance < 0.2f || distance > 1.0f)
			{
				x = Wolf::Numerical::Random::range_f(-2, 2);
				y = Wolf::Numerical::Random::range_f(-2, 2);
				distance = std::sqrt(x*x + y*y);
			}

			float angle = atan2(y, x);

			glm::vec2 velocity(-sin(angle), cos(angle));
			velocity = (1.3f * distance) * glm::normalize(velocity);
			Body body = Body{{x, y}, velocity, Wolf::Numerical::Random::range_f(10, 20)};
			_bodies.push_back(body);
		}
		*/

	}
}



