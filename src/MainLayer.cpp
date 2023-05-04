
#include "MainLayer.h"
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <glm/gtx/string_cast.hpp>
#include <queue>

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

		_points.reserve(500);
		_positive_furthest_pos = glm::vec2(1);
		_negative_furthest_pos = glm::vec2(-1);

		float max_speed_axis = 0.2f;
		_points.emplace_back(Body{{-0.1, 0}, {0, 0.01}, 3});
		_points.emplace_back(Body{{0.1, 0}, {0, -0.01}, 3});
		/*
		for (uint32_t i = 0; i < _points.capacity(); i++)
		{
			float x = Wolf::Numerical::Random::range_f(_negative_furthest_pos.x, _positive_furthest_pos.x);
			float y = Wolf::Numerical::Random::range_f(_negative_furthest_pos.y, _positive_furthest_pos.y);

			float x_vel = Wolf::Numerical::Random::range_f(-max_speed_axis, max_speed_axis);
			float y_vel = Wolf::Numerical::Random::range_f(-max_speed_axis, max_speed_axis);
			float mass = 2;//Wolf::Numerical::Random::range_f(1.0f, 1.0f);
			Body body = Body{{x, y}, {x_vel, y_vel}, mass};
			_points.push_back(body);
		}
		*/
		std::cout << "Layer started" << std::endl;
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

		float delta_seconds = 1.0f / 200.0f;//delta.seconds();

		if (_using_tree)
		{
			// Updates Barnes Hut tree
			float tree_size = std::max(abs(_negative_furthest_pos.x - _positive_furthest_pos.x), abs(_negative_furthest_pos.y - _positive_furthest_pos.y));
			_bhtree = BHTree(2.0f * tree_size, glm::vec2(-tree_size * 1.0f));

			for (Body& body : _points)
			{
				_bhtree.insert(&body);
			}

			for (Body& body : _points)
			{
				_bhtree.attract(&body, delta_seconds);
			}
		}
		else
		{
			// Calculates gravity
			float smoothing = 0.001;
			float g = 6e-5;
			for (uint32_t i = 0; i < _points.size(); i++)
			{
				Body& b1 = _points[i];
				for (uint32_t j = i + 1; j < _points.size(); j++)
				{
					Body& b2 = _points[j];
					glm::vec2 dir = b1.position - b2.position;
					float force_magnitude = g * b1.mass * b2.mass / (dir.x * dir.x + dir.y * dir.y + smoothing);
					glm::vec2 force = (delta_seconds * force_magnitude) * glm::normalize(dir);
					b2.velocity += force;
					b1.velocity -= force;
				}
			}
		}


		for (Body& body : _points)
		{
			body.position += delta_seconds * body.velocity;
			_positive_furthest_pos.x = std::max(_positive_furthest_pos.x, body.position.x);
			_positive_furthest_pos.y = std::max(_positive_furthest_pos.y, body.position.y);
			_negative_furthest_pos.x = std::min(_negative_furthest_pos.x, body.position.x);
			_negative_furthest_pos.y = std::min(_negative_furthest_pos.y, body.position.y);
		}
	}
	void MainLayer::on_ui_render_start()
	{
		ImGui::Begin("Status");
		float render_time = Application::get()->get_render_time().seconds();
		float update_time = Application::get()->get_update_time().seconds();
		ImGui::Text(("Render time: " + std::to_string(render_time)).c_str());
		ImGui::Text(("Update time: " + std::to_string(update_time)).c_str());

		if (_using_tree)
		{
			if (ImGui::Button("Brute force"))
				_using_tree = false;
		}
		else
		{
			if(ImGui::Button("Tree"))
				_using_tree = true;
		}

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
		for (const Body& body : _points)
		{
			Rendering::Renderer2D::submit_circle(glm::vec3(body.position, 0), 0.05f, color);
		}

		// Breadth first search for rendering the tree
		std::queue<BHTree> queue;
		queue.push(_bhtree);
		glm::vec4 line_color = {0, 1, .6, 1};
		float line_thickness = 0.01f;
		while (queue.size() != 0)
		{
			BHTree tree = queue.front();
			queue.pop();

			if (!tree.is_leaf())
			{
				for (const BHTree& sub_tree : tree.get_quadrants())
				{
					queue.push(sub_tree);
				}
			}

			float size = tree.get_size();
			glm::vec3 bottom_left = glm::vec3(tree.get_bottom_left(), 0.0f);
			glm::vec3 top_left = bottom_left + glm::vec3(0.0f, size, 0.0f);
			glm::vec3 top_right = bottom_left + glm::vec3(size, size, 0.0f);
			glm::vec3 bottom_right = bottom_left + glm::vec3(size, 0.0f, 0.0f);
			Rendering::Renderer2D::submit_line(bottom_left, bottom_right, line_color, line_thickness);
			Rendering::Renderer2D::submit_line(bottom_left, top_left, line_color, line_thickness);
			Rendering::Renderer2D::submit_line(top_left, top_right, line_color, line_thickness);
			Rendering::Renderer2D::submit_line(bottom_right, top_right, line_color, line_thickness);
		}
		Rendering::Renderer2D::end_frame();
		// Debug rendering
		Rendering::Renderer2D::begin_scene(_debug_camera);
		Rendering::Renderer2D::new_frame();
		Rendering::Renderer2D::end_frame();
	}
}