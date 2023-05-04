#pragma once
#ifndef BATCH_LAYER_H
#define BATCH_LAYER_H

#include "../Dependencies/Wolf/WEngine.h"
#include <unordered_map>
#include <vector>
#include "Body.h"
#include "BHTree.h"

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
			Wolf::Rendering::Camera _camera;
			Wolf::Rendering::Camera _debug_camera;
			std::unordered_map<KeyCode, bool> _key_states;
			std::vector <Body> _points;

			glm::vec2 _positive_furthest_pos;
			glm::vec2 _negative_furthest_pos;
			BHTree _bhtree;
			bool _using_tree;
	};
}

#endif