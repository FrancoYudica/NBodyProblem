#pragma once
#ifndef WOLF_MATERIAL_PROPERTY_H
#define WOLF_MATERIAL_PROPERTY_H

#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "ShaderProgram.h"

namespace Wolf
{
    namespace Rendering
    {
        enum MatPropType {
		    MatFloat, MatFloat2, MatFloat3, MatFloat4
        };
        class MaterialProperty
        {   
            public:
            MaterialProperty(const std::string& name, MatPropType type) : _name(name), _type(type){}

            inline const std::string& get_name() const { return _name; }
            inline MatPropType get_type() const { return _type; }
            virtual void upload_to_shader(const std::shared_ptr<ShaderProgram>& shader) const {
                
                std::cout << "Invalid poly" << std::endl;

            }

            // TODO - Layer
            private:
            std::string _name;
            MatPropType _type;
            uint32_t _render_layer;
        };

        class FloatProperty : public MaterialProperty
        {
            public:
            float value;
            FloatProperty(const std::string& name, float value) 
                : MaterialProperty(name, MatPropType::MatFloat), value(value){}
            
            void upload_to_shader(const std::shared_ptr<ShaderProgram>& shader) const override
            {
                shader->set_float(get_name(), value);
            }
        };

        class Float2Property : public MaterialProperty
        {
            public:
            glm::vec2 value;
            Float2Property(const std::string& name, glm::vec2 value) 
                : MaterialProperty(name, MatPropType::MatFloat2), value(value){}

            void upload_to_shader(const std::shared_ptr<ShaderProgram>& shader) const override
            {
                shader->set_float(get_name(), value);
            }
        };

        
        class Float3Property : public MaterialProperty
        {
            public:
            glm::vec3 value;
            Float3Property(const std::string& name, glm::vec3 value) 
                : MaterialProperty(name, MatPropType::MatFloat3), value(value){}

            void upload_to_shader(const std::shared_ptr<ShaderProgram>& shader) const override
            {
                shader->set_float(get_name(), value);
            }
        };

        class Float4Property : public MaterialProperty
        {
            public:
            glm::vec4 value;
            Float4Property(const std::string& name, glm::vec4 value) 
                : MaterialProperty(name, MatPropType::MatFloat4), value(value){}

            void upload_to_shader(const std::shared_ptr<ShaderProgram>& shader) const override
            {
                shader->set_float(get_name(), value);
            }
        };
    }
}

#endif