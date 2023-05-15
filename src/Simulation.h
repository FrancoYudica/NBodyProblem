#ifndef NBODY_SIMULATION_H
#define NBODY_SIMULATION_H
#include "Body.h"
#include <vector>
#include <memory>

namespace Wolf
{
    namespace Rendering
    {
        class Camera;
    }
}

class BHTree;

class Simulation
{
    public:
        Simulation() = default;
        virtual void init(uint32_t reserve_count, float size);
        virtual void add_body(glm::vec2 pos, glm::vec2 vel, float mass);
        virtual void render(const Wolf::Rendering::Camera& camera);
        virtual void debug_render(const Wolf::Rendering::Camera& camera) {}
        virtual void update(float g, float smoothing, float step){}
        void clear() { bodies.clear(); }
        uint32_t body_count() const { return bodies.size(); }

    protected:
        std::vector<Body> bodies;
        float size;
};

#endif


class SimpleSimulation : public Simulation
{
    public:
        SimpleSimulation() = default;
        void update(float g, float smoothing, float step) override;
        void render(const Wolf::Rendering::Camera& camera) override;
};

class BarnesHutSimulation : public Simulation
{
    public:
        BarnesHutSimulation() = default;
        virtual void update(float g, float smoothing, float step) override;
        virtual void render(const Wolf::Rendering::Camera& camera) override;
        virtual void debug_render(const Wolf::Rendering::Camera& camera) override;
    private:
        std::unique_ptr<BHTree> _tree;
        bool _render_tree;
};