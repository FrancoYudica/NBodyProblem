#include "Simulation.h"
#include "WEngine.h"
#include "BHTree.h"
#include <queue>

void Simulation::init(uint32_t reserve_count, float size)
{
    bodies.reserve(reserve_count);
    this->size = size;
}

void Simulation::add_body(glm::vec2 pos, glm::vec2 vel, float mass)
{
    static uint32_t id = 0;
    bodies.emplace_back(Body(id++, pos, vel, mass));
}


void Simulation::render(const Wolf::Rendering::Camera& camera)
{
    Wolf::Rendering::Renderer2D::begin_scene(camera);
    Wolf::Rendering::Renderer2D::new_frame();

    float max_color_speed = 7.0f;
    for (const Body& body : bodies)
	{
		float t = Wolf::Numerical::clamp(glm::length(body.velocity), 0.0f, max_color_speed) / max_color_speed;
		glm::vec3 color = Wolf::Numerical::lerp3<glm::vec3>({1, 1, 1}, {0, 0, 1}, {1, 0, 0}, t);
		Wolf::Rendering::Renderer2D::submit_circle(glm::vec3(body.position, 0), 0.002f * body.mass, {color, 1});
	}
    Wolf::Rendering::Renderer2D::end_frame();
}


void SimpleSimulation::update(float g, float smoothing, float step)
{
	for (uint32_t i = 0; i < bodies.size(); i++)
	{
		Body& b1 = bodies[i];
		for (uint32_t j = i + 1; j < bodies.size(); j++)
		{
			Body& b2 = bodies[j];
			glm::vec2 b2_to_b1 = b1.position - b2.position;
			float inv = g /  (b2_to_b1.x * b2_to_b1.x + b2_to_b1.y * b2_to_b1.y + smoothing);
			float magnitude_to_b1 = b2.mass * inv;
			float magnitude_to_b2 = b1.mass * inv;
			glm::vec2 norm_dir_to_b2 = glm::normalize(b2_to_b1);
			glm::vec2 b1_acceleration = -step * magnitude_to_b1 * norm_dir_to_b2;
			glm::vec2 b2_acceleration = step * magnitude_to_b2 * norm_dir_to_b2;
			b1.velocity += b1_acceleration;
			b2.velocity += b2_acceleration;
		}
	}

    for (Body& body : bodies)
        body.position += body.velocity * step;
}

void SimpleSimulation::render(const Wolf::Rendering::Camera& camera)
{
    Simulation::render(camera);
}


void BarnesHutSimulation::update(float g, float smoothing, float step)
{
	{
		auto timer = Wolf::ScopeTimer([](Wolf::Time elapsed){ std::cout << "Tree construction: " << elapsed << std::endl; });
		// Updates Barnes Hut tree
		_tree = std::make_unique<BHTree>(size, glm::vec2(-size * 0.5f), smoothing, g);

		// Inserts all the bodies
		for (Body& body : bodies)
			_tree->insert(&body);
	}

	{
		auto timer = Wolf::ScopeTimer([](Wolf::Time elapsed){ std::cout << "Attraction: " << elapsed << std::endl; });
		// Calculates acceleration, and adds to velocity - Verlet Intergration
		for (Body& body : bodies)
			_tree->attract(&body, step);
	}

	{
		auto timer = Wolf::ScopeTimer([](Wolf::Time elapsed){ std::cout << "Moving: " << elapsed << std::endl; });
		float half_tree_size = size * 0.5f;
		uint32_t index = 0;
		while(index < bodies.size())
		{
			Body& body = bodies[index];
			body.position += step * body.velocity;
			if (abs(body.position.x) > half_tree_size || abs(body.position.y) > half_tree_size)
			{
				bodies.erase(bodies.begin() + index);
			}
			else
			{
				index++;
			}
		}
	}
}

void BarnesHutSimulation::debug_render(const Wolf::Rendering::Camera& camera)
{
    auto debug_cam = Wolf::Rendering::Camera(camera.get_width(), camera.get_height(), 1);
    Wolf::Rendering::Renderer2D::begin_scene(debug_cam);
    Wolf::Rendering::Renderer2D::new_frame();

	{
		// Breadth first search for rendering the tree
		std::queue<const BHTree*> queue;
		queue.push(_tree.get());
		glm::vec4 line_color = {0, 1, .6, 1};
		float line_thickness = 0.005f;
		while (queue.size() != 0)
		{
			const BHTree* node = queue.front();
			queue.pop();
			if (!node->is_leaf())
			{
				queue.push(node->north_east());
				queue.push(node->north_west());
				queue.push(node->south_east());
				queue.push(node->south_west());
			}
			float size = node->get_size();
			glm::vec2 bl = node->get_bottom_left();
			glm::vec2 bottom_left = Wolf::Input::world_to_screem_coord(camera, bl);
			glm::vec2 top_left = Wolf::Input::world_to_screem_coord(camera, bl + glm::vec2{0, size});
			glm::vec2 top_right = Wolf::Input::world_to_screem_coord(camera, bl + glm::vec2{size});
			glm::vec2 bottom_right = Wolf::Input::world_to_screem_coord(camera, bl + glm::vec2{size, 0});
			Wolf::Rendering::Renderer2D::submit_line_interpolated(bottom_left, bottom_right, line_color, line_thickness);
			Wolf::Rendering::Renderer2D::submit_line_interpolated(bottom_left, top_left, line_color, line_thickness);
			Wolf::Rendering::Renderer2D::submit_line_interpolated(top_left, top_right, line_color, line_thickness);
			Wolf::Rendering::Renderer2D::submit_line_interpolated(bottom_right, top_right, line_color, line_thickness);
			if (node->has_body())
			{
				Body* body = node->get_body();
				//Wolf::Rendering::Renderer2D::submit_circle(glm::vec3(body->position, 0), 0.002f * body->mass, {1, 1, 1, 1});
			}
		}
	}
    Wolf::Rendering::Renderer2D::end_frame();
}

void BarnesHutSimulation::render(const Wolf::Rendering::Camera& camera)
{
    Simulation::render(camera);
}