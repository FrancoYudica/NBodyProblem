#include "BHTreeClean.h"
#include <iostream>


Tree::Tree(float size, glm::vec2 bottom_left, float smoothing, float g, uint32_t depth, Tree* parent)
    : 
    _parent(parent),
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


Tree::~Tree()
{
    if(!_is_leaf)
    {
        delete _nw;
        delete _ne;
        delete _sw;
        delete _se;
    }
}

void Tree::insert(Body* body)
{
    // First insert
    if (_body_count == 0)
    {
        _leaf_body = body;
        body->tree = this;
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
        _is_leaf = false;
    }

    // When the Tree was alrady split
    else
        _insert_child(body);

    _body_count++;
    _mass += body->mass;
    _mass_center_denominator += body->position * body->mass;
    _mass_center = _mass_center_denominator / _mass;
}


void Tree::attract(Body* body, float delta_seconds) const
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

bool Tree::translate(Body* body, float dt)
{
    body->position += body->velocity * dt;
    if (!_fits(body))
    {   
        std::cout << "Doesnt fit" << std::endl;
        // Body out of Tree bounds, inserts to parent

        _empty_leaf();
        if (_parent == nullptr)
        {
            std::cout << "Body: " << body->id << " removed" << std::endl;
            return false;
        }
        
        if (!_parent->_insert_parent(body))
        {
            std::cout << "Body: " << body->id << " removed" << std::endl;
            return false;
        }
    }
    return true;
}

bool Tree::_fits(const Body* body)
{
    return  (body->position.x > _bottom_left.x) &&
            (body->position.x < _bottom_left.x + _size) &&
            (body->position.y > _bottom_left.y) &&
            (body->position.y < _bottom_left.y + _size);
}


bool Tree::_insert_parent(Body* body)
{
    // Inserts a body that was previously contained in a child
    if (_fits(body))
    {
        _insert_child(body);
        return true;
    }
    _body_count--;
    _mass -= body->mass;
    _mass_center_denominator -= body->position * body->mass;
    _mass_center = _mass_center_denominator / _mass;

    if (_body_count == 1)
    {   
        Body* child_body = nullptr;

        if (_nw->_body_count == 1)
            child_body = _nw->_leaf_body;
        else if(_ne->_body_count == 1)
            child_body = _ne->_leaf_body;
        else if(_sw->_body_count == 1)
            child_body = _sw->_leaf_body;
        else if (_se->_body_count == 1)
            child_body = _se->_leaf_body;
        else       
            assert(false);

        // Makes a leaf with this body
        _is_leaf = true;
        _leaf_body = child_body;
        _leaf_body->tree = this;
        _mass = _leaf_body->mass;
        _mass_center = _leaf_body->position;
        _mass_center_denominator = _leaf_body->position * _leaf_body->mass;

        delete _nw;
        delete _ne;
        delete _sw;
        delete _se;
    }

    if (_parent == nullptr)
        return false;

    return _parent->_insert_parent(body);
}

void Tree::_empty_leaf()
{
    _is_leaf = true;
    _body_count = 0;
    _mass = 0;
    _mass_center = glm::vec2{0};
    _mass_center_denominator = glm::vec2{0};
    _leaf_body = nullptr;
}


void Tree::_split()
{
    // Uses cartesian order
    float size = 0.5f * _size;
    _nw = new Tree(size, _bottom_left + glm::vec2(0.0f, size), _smoothing, _g, _depth + 1, this);
    _ne = new Tree(size, _bottom_left + glm::vec2(size, size), _smoothing, _g, _depth + 1, this);
    _se = new Tree(size, _bottom_left + glm::vec2(size, 0.0f), _smoothing, _g, _depth + 1, this);
    _sw = new Tree(size, _bottom_left, _smoothing, _g, _depth + 1, this);
}

void Tree::_insert_child(Body* body) 
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
