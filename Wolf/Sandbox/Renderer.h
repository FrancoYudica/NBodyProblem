#pragma once
#ifndef WOLF_BATCH_RENDERER_H
#define WOLF_BATCH_RENDERER_H

#include <glm/glm.hpp>

class Renderer2D
{
	/*
	* 2D Quad batch renderer
	*/
public:
	static void Init();
	static void Shutdown();
	static void NewFrame();
	static void EndFrame();
	static void SubmitQuad(const glm::vec3& position, const glm::vec3 size, const glm::vec4& color);
private:
	static void _Flush();
};

#endif
