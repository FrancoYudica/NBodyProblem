#pragma once
#ifndef WOLF_MATERIAL_H
#define WOLF_MATERIAL_H

#include "MaterialAttribute.h"
#include <vector>

namespace Wolf
{
    namespace Rendering
    {
        class Material
        {
            public:
            Material() = default;

            bool contains_property(const std::string& name) const;
            std::shared_ptr<MaterialProperty>& get_property(const std::string& name);
            inline const std::shared_ptr<ShaderProgram>& get_shader() const { return _shader; }
            void set_shader_program(const std::shared_ptr<ShaderProgram>& shader);
            void upload() const;

            void add_float(const std::string& name, float value);
            void add_float2(const std::string& name, glm::vec2 value);
            void add_float3(const std::string& name, glm::vec3 value);
            void add_float4(const std::string& name, glm::vec4 value);

            private:
            void _control_existing_property(const std::string& attr);

            private:
            std::vector<std::shared_ptr<MaterialProperty>> _properties;
            std::shared_ptr<ShaderProgram> _shader;
        };
    }
}

#endif