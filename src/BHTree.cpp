#include "BHTree.h"

BHTree::BHTree(float size, glm::vec2 bottom_left)
    : _size(size), _bottom_left(bottom_left),
      _mass(0.0f), _mass_center(glm::vec2(0.0f)), 
      _is_leaf(true), _body_count(0), _mass_center_denominator({0.0f}), _leaf_body(nullptr)
{
    _center = _bottom_left + glm::vec2(size * 0.5f);
    // Empty body
}

void BHTree::insert(Body* body)
{
    if (_body_count == 0)
    {
        _leaf_body = body;
        _is_leaf = true;
    }

    // When it has just one body
    else if (_is_leaf)
    {
        _split();

        // Inserts both objects
        _quadrants[_get_quadrant_index(_leaf_body)].insert(_leaf_body);        
        _quadrants[_get_quadrant_index(body)].insert(body);        
        _is_leaf = false;
    }

    // When the Tree was alrady split
    else
    {
        _quadrants[_get_quadrant_index(body)].insert(body);
    }

    _body_count++;
    _mass += body->mass;
    _mass_center_denominator += body->position * body->mass;
    _mass_center = _mass_center_denominator / _mass;
}

void BHTree::attract(Body* body, float delta_seconds) const
{
    if (_body_count == 0 || body == _leaf_body)
        return;

    float g = 6e-5;
    float smoothing = 0.001f;
    if (_is_leaf)
    {
		glm::vec2 dir = body->position - _leaf_body->position;
		float force_magnitude = g * body->mass * _leaf_body->mass / (dir.x * dir.x + dir.y * dir.y + smoothing);
		glm::vec2 force = (delta_seconds * force_magnitude) * glm::normalize(dir);
		_leaf_body->velocity += force;
		body->velocity -= force;
        return;
    }

    
    glm::vec2 dir = body->position - _mass_center;
    float distance = length(dir);
    if (_size / distance < 0.5f)
    {
		float force_magnitude = g * body->mass * _mass / (dir.x * dir.x + dir.y * dir.y + smoothing);
		glm::vec2 force = (delta_seconds * force_magnitude) * (dir / distance);
		body->velocity -= force;
    }

    else
    {
        _quadrants[0].attract(body, delta_seconds);
        _quadrants[1].attract(body, delta_seconds);
        _quadrants[3].attract(body, delta_seconds);
        _quadrants[3].attract(body, delta_seconds);
    }
}
void BHTree::_split()
{
    // Uses cartesian order
    float size = 0.5f * _size;
    glm::vec2 quadrant0_pos = _bottom_left + glm::vec2(size, size);
    glm::vec2 quadrant1_pos = _bottom_left + glm::vec2(0.0f, size); 
    glm::vec2 quadrant2_pos = _bottom_left; 
    glm::vec2 quadrant3_pos = _bottom_left + glm::vec2(size, 0.0f); 

    _quadrants.emplace_back(BHTree(size, quadrant0_pos));
    _quadrants.emplace_back(BHTree(size, quadrant1_pos));
    _quadrants.emplace_back(BHTree(size, quadrant2_pos));
    _quadrants.emplace_back(BHTree(size, quadrant3_pos));
}

uint32_t BHTree::_get_quadrant_index(Body* body) const
{

    // In the right side
    if (body->position.x >= _center.x)
        return (body->position.y >= _center.y) ? 0 : 3;
    
    // In the left side
    return (body->position.y >= _center.y) ? 1 : 2;
}