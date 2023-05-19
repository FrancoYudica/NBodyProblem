#pragma once
#ifndef BATCH_LAYER_H
#define BATCH_LAYER_H

#include "WEngine.h"
#include <unordered_map>
#include <vector>
#include "Body.h"
#include "BHTree.h"
#include "BHTreeClean.h"
#include <memory>
#include "Simulation.h"

using namespace Wolf;

namespace NBody
{


	class MainLayer : public Wolf::Layer
	{
		public:
			MainLayer() = default;
			virtual void on_start() override;
			virtual void on_end() override;
			virtual void on_update(const Time& delta) override;
			virtual void on_event(Event* event) override;
			virtual void on_ui_render_start() override;
			virtual void on_ui_render_finish() override;
			virtual void on_render() override;

		private:
			void _reset_simulation();
		private:
			Wolf::Rendering::Camera _camera;
			Wolf::Rendering::Camera _debug_camera;

			float _simulation_speed;
			float _simulation_size;
			bool _debug_render;
			glm::vec2 _clicked_position;
			std::unique_ptr<Simulation> _simulation;

	};
}

#endif