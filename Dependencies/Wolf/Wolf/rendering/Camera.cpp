#include "Camera.h"

namespace Wolf
{
    namespace Rendering
    {
        Camera::Camera(uint32_t width, uint32_t height, float zoom=1.0f)  
            : _width(width), _height(height), _zoom(zoom), _position(glm::vec3(0.0f)) {
            on_viewport_resize(width, height);
            _recalculate_view();

        }
        void Camera::set_position(glm::vec3 position)
        {
            _position = position;
            _recalculate_view();
        }
        
        void Camera::set_zoom(float zoom)
        {
            _zoom = zoom;
            _recalculate_projection();
        }

        void Camera::on_viewport_resize(uint32_t width, uint32_t height)
        {
            _width = width;
            _height = height;
            _aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
            _recalculate_projection();
        }

        void Camera::_recalculate_projection()
        {
            float width = _aspect_ratio / _zoom;
            float height = 1.0f / _zoom;

            float left = -width;
            float right = width;
            float bottom = -height;
            float top = height;
            _projection_matrix = glm::ortho(left, right, bottom, top);
        }

        void Camera::_recalculate_view()
        {
            glm::mat4 transform = glm::translate(glm::mat4(1), _position);
            _view_matrix = glm::inverse(transform);
        }

    }
}