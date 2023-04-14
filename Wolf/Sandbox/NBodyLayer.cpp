#include "NBodyLayer.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Random.h"


namespace Wolf
{
	namespace SandboxLayers
	{

		void NBodyLayer::on_start()
		{
			Renderer2D::Init();

			for (uint32_t i = 0; i < 10; i++)
			{
				_Particles.push_back(Random::UnitVec2());
			}

		}
		void NBodyLayer::on_update(const Time& delta)
		{

		}
		void NBodyLayer::on_event(const Event& event)
		{
		}
		void NBodyLayer::on_ui_render_start()
		{
		}
		void NBodyLayer::on_ui_render_finish()
		{
		}
		void NBodyLayer::on_end()
		{
		}
		void NBodyLayer::on_render()
		{
			Rendering::RenderCommand::Clear();
			Renderer2D::NewFrame();

			for (glm::vec2& pos : _Particles)
			{
				Renderer2D::SubmitQuad(glm::vec3(pos, 0), glm::vec3(.1), glm::vec4(1));
			}

			Renderer2D::EndFrame();
		}
	}
}

