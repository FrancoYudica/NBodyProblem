#include "Renderer.h"
#include <memory>
#include "Material.h"
#include "batch/Batch.h"
#include "batch/SpriteBatch.h"
#include "batch/CircleBatch.h"
#include "batch/LineBatch.h"
#include "glm/gtc/matrix_transform.hpp"

using namespace Wolf::Rendering;

struct RendererData
{
	SpriteBatch sprite_batch;
	CircleBatch circle_batch;
	LineBatch line_batch;
};

// Data used for the renderer
static RendererData _data;

void Renderer2D::init()
{

	// Gets the default material for SpriteBatch
	const Path assets_path = Wolf::PathManager::get_instance().get_engine_assets_path();
	{
		const Path vertex_path = assets_path / "shaders/default_sprite/renderer2d.vert";
		const Path fragment_path = assets_path / "shaders/default_sprite/renderer2d.frag";
		auto _material = std::make_shared<Material>();
		_material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));
		_data.sprite_batch.init(_material);
	}

	{
		const Path vertex_path = assets_path / "shaders/default_circle/circle.vert";
		const Path fragment_path = assets_path / "shaders/default_circle/circle.frag";
		auto _material = std::make_shared<Material>();
		_material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));
		_data.circle_batch.init(_material);
	}

	{
		const Path vertex_path = assets_path / "shaders/default_line/line.vert";
		const Path fragment_path = assets_path / "shaders/default_line/line.frag";
		auto _material = std::make_shared<Material>();
		_material->set_shader_program(ShaderProgram::create(vertex_path, fragment_path));
		_data.line_batch.init(_material);
	}
}

void Renderer2D::begin_scene(const Camera& camera)
{
	_data.sprite_batch.begin_scene(camera);
	_data.circle_batch.begin_scene(camera);
	_data.line_batch.begin_scene(camera);
}

void Renderer2D::shutdown()
{
	_data.sprite_batch.shutdown();
	_data.circle_batch.shutdown();
	_data.line_batch.shutdown();
}

void Renderer2D::new_frame()
{
	_data.sprite_batch.new_frame();
	_data.circle_batch.new_frame();
	_data.line_batch.new_frame();
}

void Renderer2D::end_frame()
{
	_data.sprite_batch.end_frame();
	_data.circle_batch.end_frame();
	_data.line_batch.end_frame();
}

void Renderer2D::submit_quad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	_data.sprite_batch.submit_primitive(position, size, color);
}


void Renderer2D::submit_circle(const glm::vec3& position, const float radius, const glm::vec4& color, float fade)
{
	_data.circle_batch.submit_primitive(position, radius, color, fade);
}

void Renderer2D::submit_line(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, const float thickness)
{
	_data.line_batch.submit_primitive(p0, p1, color, thickness);
}


void Renderer2D::submit_line_interpolated(const glm::vec3& p0, const glm::vec3& p1, const glm::vec4& color, const float thickness)
{
	_data.line_batch.submit_primitive_interpolated(p0, p1, color, thickness);
}