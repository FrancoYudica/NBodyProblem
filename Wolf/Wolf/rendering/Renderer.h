#pragma once
#ifndef WOLF_BATCH_RENDERER_H
#define WOLF_BATCH_RENDERER_H

#include <glm/glm.hpp>
#include <memory>
#include "Buffer.h"
#include "VertexArray.h"

namespace Wolf
{
	namespace Rendering
	{

		struct QuadVertex
		{
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 uv;
			unsigned int texture_index;
		};


		struct RendererData
		{
			unsigned int BatchSize; // Max amount of Quads, (4 QuadVertex per quad)
			unsigned int Submitions;
			std::shared_ptr<Wolf::Rendering::VertexArray> VAO;
			std::shared_ptr<Wolf::Rendering::VertexBuffer> VBO;
			std::shared_ptr<Wolf::Rendering::IndexBuffer> IBO;
			std::vector<QuadVertex> Vertices;
		};

		class Renderer2D
		{
			/*
			* 2D Quad batch renderer
			*/

		public:
			static void Init();
			static void NewFrame();
			static void EndFrame();
			static void SubmitQuad(const glm::vec3& position, const glm::vec3 size, const glm::vec4& color);
		private:
			static void _Flush();
		private:
			static RendererData _Data;

		};

	}
}

#endif
