#pragma once
#ifndef WOLF_ENGINE_INCLUDE_H
#define WOLF_ENGINE_INCLUDE_H

#include <glm/glm.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include <string>

// Core includes
#include "Wolf/core/Application.h"
#include "Wolf/core/Event.h"
#include "Wolf/core/Time.h"
#include "Wolf/core/Layer.h"
#include "Wolf/core/Window.h"

// ImGui layer
#include "Wolf/imgui_layer/imgui_layer.h"

// Rendering
#include "Wolf/rendering/ShaderProgram.h"
#include "Wolf/rendering/Buffer.h"
#include "Wolf/rendering/VertexArray.h"
#include "Wolf/rendering/Renderer.h"
#include "Wolf/rendering/RenderCommand.h"
#include "Wolf/rendering/Camera.h"

// Numerical
#include "Wolf/numerical/Random.h"

// Utils
#include "Wolf/utils/File.h"
#include "Wolf/utils/PathManager.h"
#include "Wolf/entry_point.h"

// Input
#include "Wolf/input/input_transform.h"
#include "Wolf/input/input.h"

#endif