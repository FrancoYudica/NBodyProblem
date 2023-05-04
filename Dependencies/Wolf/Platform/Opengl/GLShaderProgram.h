#pragma once
#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "rendering/ShaderProgram.h"
#include <glm/glm.hpp>

namespace Wolf
{
	namespace Rendering
	{
		namespace GL
		{


			class GLShaderProgram : public Wolf::Rendering::ShaderProgram
			{

			public:

				unsigned int ID;
				GLShaderProgram() = default;
				GLShaderProgram(const string& vertex_src, const string& fragment_src);
				void bind() override;
				void unbind() override;
				void set_float(const string& name, float value) const override;
				void set_float(const string& name, const glm::vec2& value) const override;
				void set_float(const string& name, const glm::vec3& value) const override;
				void set_float(const string& name, const glm::vec4& value) const override;
				void set_matrix(const string& name, const glm::mat4& matrix) const override;
				void set_int(const string& name, int value) const override;

			private:
				unsigned int compile_shader(const string& source, unsigned int type);
			};

		}
	}
}
#endif