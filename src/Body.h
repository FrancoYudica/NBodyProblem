#pragma once
#ifndef NBODY_BODY_H
#define NBODY_BODY_H

#include <glm/glm.hpp>

class Tree;

struct Body{

	Body(uint32_t id, glm::vec2 pos, glm::vec2 vel, float m) : id(id), position(pos), velocity(vel), mass(m), tree(nullptr){}
	uint32_t id;
	glm::vec2 position;
	glm::vec2 velocity;
	float mass;
	Tree* tree;
};

#endif