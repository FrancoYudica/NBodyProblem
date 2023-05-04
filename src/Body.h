#ifndef NBODY_BODY_H
#define NBODY_BODY_H
#include <glm/glm.hpp>

struct Body{
	glm::vec2 position;
	glm::vec2 velocity;
	float mass;
};

#endif