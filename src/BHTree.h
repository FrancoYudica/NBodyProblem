#ifndef NBODY_BARNES_HUT_H
#define NBODY_BARNES_HUT_H
#include "Body.h"
#include <vector>

class BHTree
{

    public:
        BHTree() = default;
        BHTree(float size, glm::vec2 bottom_left);
        void insert(const Body* body);
        void attract(Body* body, float delta_seconds) const;
        float get_size() const { return _size; }
        glm::vec2 get_bottom_left() const { return _bottom_left; }
        bool is_leaf() const { return _is_leaf; }
        const std::vector<BHTree>& get_quadrants() const { return _quadrants; }

    private:
        void _split();
        uint32_t _get_quadrant_index(const Body* body) const;

    private:
        glm::vec2 _bottom_left;
        float _size;
        bool _is_leaf;
        uint32_t _body_count;

        float _mass;
        glm::vec2 _mass_center;
        glm::vec2 _mass_center_denominator;
        glm::vec2 _center;
        const Body* _leaf_body;
        std::vector<BHTree> _quadrants;
};



#endif
