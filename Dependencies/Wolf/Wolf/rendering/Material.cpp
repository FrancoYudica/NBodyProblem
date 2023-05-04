#include "Material.h"
#include <tuple>

using namespace Wolf::Rendering;


bool Material::contains_property(const std::string& name) const
{
    for (auto& prop: _properties)
        if (prop->get_name() == name) return true;

    return false;
}

void Material::_control_existing_property(const std::string& name)
{
    // Used to show warings when the attribute exists
    if (contains_property(name))
    {
        std::cout << "Property: " << name << ", already contained in material" << std::endl;
        return;
    }
}

void Material::add_float(const std::string& name, float value)
{
    _control_existing_property(name);
    _properties.push_back(std::make_shared<FloatProperty>(name, value));
}

void Material::add_float2(const std::string& name, glm::vec2 value)
{
    _control_existing_property(name);
    _properties.push_back(std::make_shared<Float2Property>(name, value));
}

void Material::add_float3(const std::string& name, glm::vec3 value)
{
    _control_existing_property(name);
    _properties.push_back(std::make_shared<Float3Property>(name, value));
}

void Material::add_float4(const std::string& name, glm::vec4 value)
{
    _control_existing_property(name);
    _properties.push_back(std::make_shared<Float4Property>(name, value));
}



void Material::set_shader_program(const std::shared_ptr<ShaderProgram>& shader)
{
    // Creates a copy of the shader_ptr
    _shader = shader;
}
void Material::upload() const
{
    // Uploads all the uniform data
    _shader->bind();

    for (auto& prop : _properties)
        prop->upload_to_shader(_shader);
}

std::shared_ptr<MaterialProperty>& Material::get_property(const std::string& name)
{
    for (auto& prop : _properties)
        if (prop->get_name() == name) return prop;

    std::cout << "Unable to find property named: " << name << std::endl;
    // TODO -- Raise exception
}