#ifndef NBODY_BARNES_HUT_H
#define NBODY_BARNES_HUT_H
#include "Body.h"
#include <vector>
#include <memory>

class BHTree
{

    public:
        BHTree() = default;
        ~BHTree();
        BHTree(float size, glm::vec2 bottom_left, float smoothing, float g, uint32_t depth=0);
        void insert(const Body* body);
        void attract(Body* body, float delta_seconds) const;

        // Getters
        inline float get_size() const { return _size; }
        inline glm::vec2 get_bottom_left() const { return _bottom_left; }
        inline bool is_leaf() const { return _is_leaf; }
        inline uint32_t get_depth() const { return _depth; }
        
        inline const BHTree* north_west() const { return _nw; }
        inline const BHTree* north_east() const { return _ne; }
        inline const BHTree* south_west() const { return _sw; }
        inline const BHTree* south_east() const { return _se; }

    private:
        void _insert_child(const Body* body);
        void _split();

    private:
        float _smoothing;
        float _g;
        glm::vec2 _bottom_left;
        float _size;
        bool _is_leaf;
        uint32_t _body_count;
        uint32_t _depth;
        float _mass;
        glm::vec2 _mass_center;
        glm::vec2 _mass_center_denominator;
        glm::vec2 _center;
        const Body* _leaf_body;

        BHTree* _nw;
        BHTree* _ne;
        BHTree* _sw;
        BHTree* _se;
};



#endif
