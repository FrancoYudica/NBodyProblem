#pragma once
#ifndef WOLF_CAMERA_H
#define WOLF_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Wolf
{
    namespace Rendering
    {

        struct Camera
        {
            public:
                Camera() = default;
                Camera(uint32_t width, uint32_t height, float zoom);
                void on_viewport_resize(uint32_t width, uint32_t height);

                void set_position(glm::vec3 position);
                inline glm::vec3 get_position() const { return _position; }

                void set_zoom(float zoom);
                inline float get_zoom() const { return _zoom; }

                inline float get_aspect_ratio() const { return _aspect_ratio; }

                inline const glm::mat4& get_projection() const { return _projection_matrix; }
                inline const glm::mat4& get_view() const { return _view_matrix; }

            private:
                void _recalculate_view();
                void _recalculate_projection();

            private:
                glm::mat4 _projection_matrix;
                glm::mat4 _view_matrix;
                float _aspect_ratio;
                float _zoom;
                uint32_t _width;
                uint32_t _height;
                glm::vec3 _position;
        };
    }
}


#endif