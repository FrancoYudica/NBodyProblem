#include "BHTree.h"
#include <iostream>


BHTree::BHTree(float size, glm::vec2 bottom_left, float smoothing, float g, uint32_t depth)
    : 
    _size(size), 
    _bottom_left(bottom_left),
    _smoothing(smoothing),
    _g(g),
    _mass(0.0f),
    _mass_center(glm::vec2(0.0f)),
    _depth(depth),
    _is_leaf(true), 
    _body_count(0),
    _mass_center_denominator({0.0f}),
    _leaf_body(nullptr),
    _center(bottom_left + glm::vec2(size * 0.5)) {}


BHTree::~BHTree()
{
    if(!_is_leaf)
    {
        delete _nw;
        delete _ne;
        delete _sw;
        delete _se;
    }
}

void BHTree::insert(Body* body)
{
    // First insert
    if (_body_count == 0)
    {
        _leaf_body = body;
        _is_leaf = true;
    }

    // Second insert
    else if (_is_leaf)
    {
        _split();

        // Inserts both objects
        _insert_child(_leaf_body);
        _insert_child(body);
        _leaf_body = nullptr;
    }

    // When the Tree was alrady split
    else
        _insert_child(body);

    _body_count++;
    _mass += body->mass;
    _mass_center_denominator += body->position * body->mass;
    _mass_center = _mass_center_denominator / _mass;
}


void BHTree::attract(Body* body, float delta_seconds) const
{
    if (_body_count == 0 || body == _leaf_body)
       return;

    if (_is_leaf)
    {
		glm::vec2 dir = _leaf_body->position - body->position;
		float acceleration_magnitude = _g * _leaf_body->mass / (dir.x * dir.x + dir.y * dir.y + _smoothing);
		glm::vec2 acceleration = (delta_seconds * acceleration_magnitude) * glm::normalize(dir);
		body->velocity += acceleration;
        return;
    }

    glm::vec2 dir = _mass_center - body->position;
    float distance = length(dir);
    if (_size / distance < 0.5f)
    {
		float acceleration_magnitude = _g * _mass / (dir.x * dir.x + dir.y * dir.y + _smoothing);
		glm::vec2 acceleration = (delta_seconds * acceleration_magnitude) * (dir / distance);
		body->velocity += acceleration;
        return;
    }

    _ne->attract(body, delta_seconds);
    _nw->attract(body, delta_seconds);
    _se->attract(body, delta_seconds);
    _sw->attract(body, delta_seconds);

}
void BHTree::_split()
{
    _is_leaf = false;
    // Uses cartesian order
    float size = 0.5f * _size;
    _nw = new BHTree(size, _bottom_left + glm::vec2(0.0f, size), _smoothing, _g, _depth + 1);
    _ne = new BHTree(size, _bottom_left + glm::vec2(size, size), _smoothing, _g, _depth + 1);
    _se = new BHTree(size, _bottom_left + glm::vec2(size, 0.0f), _smoothing, _g, _depth + 1);
    _sw = new BHTree(size, _bottom_left, _smoothing, _g, _depth + 1);
}

void BHTree::_insert_child(Body* body) 
{

    // East
    if (body->position.x >= _center.x)
    {
        // North
        if (body->position.y >= _center.y)
            _ne->insert(body);

        // South
        else
            _se->insert(body);
    }

    // West
    else
    {
        // North
        if (body->position.y >= _center.y)
            _nw->insert(body);

        // South
        else
            _sw->insert(body);
    }

}
