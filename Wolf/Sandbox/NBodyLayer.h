#pragma once
#ifndef OPENGL_LAYER_H
#define OPENGL_LAYER_H

#include "../WEngine.h"

namespace Wolf
{
	namespace SandboxLayers
	{

		class NBodyLayer : public Wolf::Layer
		{
			public:
				NBodyLayer() = default;
				virtual void on_start();
				virtual void on_update(const Time& delta);
				virtual void on_event(const Event& event);
				virtual void on_ui_render_start();
				virtual void on_ui_render_finish();
				virtual void on_end();
				virtual void on_render();

			private:
				std::vector<glm::vec2> _Particles;
		};
	}
}

#endif