
#include "MainLayer.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <glm/gtx/string_cast.hpp>
#include <queue>
#include <execution>

template<typename T>
static T clamp(T a, T min, T max)
{
	if (a > max)
		return max;
	
	return (a < min) ? min : a;
}

namespace NBody
{
	void MainLayer::on_start()
	{
		Rendering::Renderer2D::init();
		Window* window = Application::get()->get_main_window();
		_camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);
		_debug_camera = Wolf::Rendering::Camera(window->get_width(), window->get_height(), 1);
		_key_states[KeyCode::KEY_W] = false;
		_key_states[KeyCode::KEY_D] = false;
		_key_states[KeyCode::KEY_S] = false;
		_key_states[KeyCode::KEY_A] = false;
		_using_tree = true;
		_paralell_execution = false;
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
		dispatcher.dispatch<KeyDownEvent>(
			EventType::KeyDown,
			[this](KeyDownEvent* key_event){
				_key_states[key_event->key] = true;
				return false;
			}
		);
		dispatcher.dispatch<KeyUpEvent>(
			EventType::KeyUp,
			[this](KeyUpEvent* key_event){
				_key_states[key_event->key] = false;
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
				auto pos = Wolf::Input::get_mouse_pos_norm();

				std::cout << pos.x << ", " << pos.y << std::endl;
				glm::vec2 position = Wolf::Input::get_world_coordinates(_camera, pos);
				glm::vec2 p1 = Wolf::Input::get_local_coordinates(_camera, position);
				std::cout << p1.x << ", " << p1.y << std::endl;

				_bodies.emplace_back(Body{position, {0, 0}, 20});
				return false;
			}
		);
		
	}
	void MainLayer::on_update(const Time& delta)
	{
		
		// Updates camera translation
		float speed = 2.0f * delta.seconds() / _camera.get_zoom();
		glm::vec3 direction(0);
		if (_key_states[KeyCode::KEY_W])
			direction += glm::vec3(0, 1, 0);
		if (_key_states[KeyCode::KEY_S])
			direction += glm::vec3(0, -1, 0);
		if (_key_states[KeyCode::KEY_D])
			direction += glm::vec3(1, 0, 0);
		if (_key_states[KeyCode::KEY_A])
			direction += glm::vec3(-1, 0, 0);
		_camera.set_position(_camera.get_position() + direction * speed);

		float delta_seconds = 1.0f / 200.0f; //delta.seconds();
		float smoothing = 0.001;
		float g = 6e-4;
		if (_using_tree)
		{
			// Updates Barnes Hut tree
			float tree_size = std::max(abs(_negative_furthest_pos.x - _positive_furthest_pos.x), abs(_negative_furthest_pos.y - _positive_furthest_pos.y));
			_bhtree = std::make_unique<BHTree>(2.0f * tree_size, glm::vec2(-tree_size * 1.0f), smoothing, g);

			// Inserts all the bodies
			for (Body& body : _bodies)
				_bhtree->insert(&body);


			if (_paralell_execution)
			{
				std::vector<uint32_t> indices = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
				std::for_each(
					std::execution::par,
					indices.begin(),
					indices.end(),
					[this, delta_seconds](uint32_t start_index)
					{
						for (uint32_t i = start_index; i < start_index + 1000; i++)
							_bhtree->attract(&_bodies[i], delta_seconds);
					}
				);
			}
			else
			{
				// Calculates acceleration, and adds to velocity - Verlet Intergration
				for (Body& body : _bodies)
					_bhtree->attract(&body, delta_seconds);
			}
		}
		else
		{
			// Calculates gravity

			for (uint32_t i = 0; i < _bodies.size(); i++)
			{
				Body& b1 = _bodies[i];
				for (uint32_t j = i + 1; j < _bodies.size(); j++)
				{
					Body& b2 = _bodies[j];
					glm::vec2 b2_to_b1 = b1.position - b2.position;
					float inv = g /  (b2_to_b1.x * b2_to_b1.x + b2_to_b1.y * b2_to_b1.y + smoothing);

					float magnitude_to_b1 = b2.mass * inv;
					float magnitude_to_b2 = b1.mass * inv;

					glm::vec2 norm_dir_to_b2 = glm::normalize(b2_to_b1);

					glm::vec2 b1_acceleration = -delta_seconds * magnitude_to_b1 * norm_dir_to_b2;
					glm::vec2 b2_acceleration = delta_seconds * magnitude_to_b2 * norm_dir_to_b2;
					b1.velocity += b1_acceleration;
					b2.velocity += b2_acceleration;
				}
			}
		}

		if (_paralell_execution)
		{
			std::for_each(
				std::execution::par,
				_bodies.begin(),
				_bodies.end(),
				[this, delta_seconds](Body& body)
				{
					body.position += delta_seconds * body.velocity;
					_positive_furthest_pos.x = std::max(_positive_furthest_pos.x, body.position.x);
					_positive_furthest_pos.y = std::max(_positive_furthest_pos.y, body.position.y);
					_negative_furthest_pos.x = std::min(_negative_furthest_pos.x, body.position.x);
					_negative_furthest_pos.y = std::min(_negative_furthest_pos.y, body.position.y);
				}
			);
		}
		else
		{
			for (Body& body : _bodies)
			{
				body.position += delta_seconds * body.velocity;
				_positive_furthest_pos.x = std::max(_positive_furthest_pos.x, body.position.x);
				_positive_furthest_pos.y = std::max(_positive_furthest_pos.y, body.position.y);
				_negative_furthest_pos.x = std::min(_negative_furthest_pos.x, body.position.x);
				_negative_furthest_pos.y = std::min(_negative_furthest_pos.y, body.position.y);
			}
		}
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
		std::string a = "Body count: " + std::to_string(_bodies.size());
		ImGui::Text(a.c_str());
		
		if (_using_tree)
		{
			if (ImGui::Button("Method -> Brute force"))
				_using_tree = false;
		}
		else
		{
			if(ImGui::Button("Method -> Tree"))
				_using_tree = true;
		}

		ImGui::Checkbox("Render BHTree", &_render_tree);
		ImGui::Checkbox("Paralell execution", &_paralell_execution);

		if (ImGui::Button("Reset simulation"))
			_reset_simulation();


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
		
		// Renders objects
		Rendering::Renderer2D::begin_scene(_camera);
		Rendering::Renderer2D::new_frame();
		auto color = glm::vec4(1.0f);
		float max_color_speed = 4.0f;
		for (const Body& body : _bodies)
		{
			float t = clamp(glm::length(body.velocity), 0.0f, max_color_speed) / max_color_speed;
			glm::vec3 c = glm::vec3(1) + t * (glm::vec3(1, -1, -.51));
			Rendering::Renderer2D::submit_circle(glm::vec3(body.position, 0), 0.005f * body.mass, glm::vec4(c, 1));
		}

		if (_render_tree)
		{
			// Breadth first search for rendering the tree
			std::queue<const BHTree*> queue;
			queue.push(_bhtree.get());
			glm::vec4 line_color = {0, 1, .6, 1};
			float line_thickness = 0.01f;

			while (queue.size() != 0)
			{
				const BHTree* tree = queue.front();
				queue.pop();

				if (!tree->is_leaf())
				{
					queue.push(tree->north_east());
					queue.push(tree->north_west());
					queue.push(tree->south_east());
					queue.push(tree->south_west());
				}

				float size = tree->get_size();
				glm::vec3 bottom_left = glm::vec3(tree->get_bottom_left(), 0.0f);
				glm::vec3 top_left = bottom_left + glm::vec3(0.0f, size, 0.0f);
				glm::vec3 top_right = bottom_left + glm::vec3(size, size, 0.0f);
				glm::vec3 bottom_right = bottom_left + glm::vec3(size, 0.0f, 0.0f);
				Rendering::Renderer2D::submit_line(bottom_left, bottom_right, line_color, line_thickness);
				Rendering::Renderer2D::submit_line(bottom_left, top_left, line_color, line_thickness);
				Rendering::Renderer2D::submit_line(top_left, top_right, line_color, line_thickness);
				Rendering::Renderer2D::submit_line(bottom_right, top_right, line_color, line_thickness);
			}
		}

		glm::vec2 local_pos = Wolf::Input::get_world_coordinates(_camera, glm::vec3(0));
		Rendering::Renderer2D::submit_circle(glm::vec3(local_pos, 0), 0.1, glm::vec4(0, 1, 0, 1));
		Rendering::Renderer2D::end_frame();

		// Debug rendering
		Rendering::Renderer2D::begin_scene(_debug_camera);
		Rendering::Renderer2D::new_frame();
		Rendering::Renderer2D::end_frame();
	}

	void MainLayer::_reset_simulation()
	{
		_bodies.clear();
		_bodies.reserve(4000);

		_positive_furthest_pos = glm::vec2(10);
		_negative_furthest_pos = glm::vec2(10);
		float max_speed_axis = 0.5f;

		for (uint32_t i = 0; i < 250; i++)
		{
			float x = Wolf::Numerical::Random::range_f(-2, -.5f);
			float y = Wolf::Numerical::Random::range_f(-1, 0.4);

			float x_vel = Wolf::Numerical::Random::range_f(0, 0);
			float y_vel = Wolf::Numerical::Random::range_f(0, .5);
			float mass = Wolf::Numerical::Random::range_f(5.0f, 15.0f);
			Body body = Body{{x, y}, {x_vel, y_vel}, mass};
			_bodies.push_back(body);
		}

		for (uint32_t i = 0; i < 250; i++)
		{
			float x = Wolf::Numerical::Random::range_f(0.5, 2);
			float y = Wolf::Numerical::Random::range_f(-1, 0.4);

			float x_vel = Wolf::Numerical::Random::range_f(0, 0);
			float y_vel = Wolf::Numerical::Random::range_f(0, -.5);
			float mass = Wolf::Numerical::Random::range_f(5.0f, 15.0f);
			Body body = Body{{x, y}, {x_vel, y_vel}, mass};
			_bodies.push_back(body);
		}


		_positive_furthest_pos = glm::vec2(4);
		_negative_furthest_pos = glm::vec2(-4);

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
	}
}



