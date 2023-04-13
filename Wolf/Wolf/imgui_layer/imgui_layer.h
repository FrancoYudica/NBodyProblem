#pragma once
#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "../core/Layer.h"

namespace Wolf
{
	namespace Layers
	{
		class ImGuiLayer : public Layer
		{
		public:
			ImGuiLayer() = default;
			virtual void on_start();
			virtual void on_update(const Time& delta);
			virtual void on_event(const Event& event);
			virtual void on_ui_render_start();
			virtual void on_ui_render_finish();
			virtual void on_end();
			virtual void on_render();
		};
	}
}


#endif
