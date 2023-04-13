#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <string>
#include <unordered_map>
#include <iostream>
#include <glm/glm.hpp>
#include <memory>

namespace Wolf
{
	namespace Rendering
	{
		class ShaderProgram
		{

		public:
			ShaderProgram() = default;
			ShaderProgram(const char* vertex_shader_patht, const char* fragment_shader_path);
			virtual void bind();
			virtual void unbind();

			virtual void set_float(const std::string& name, float value);
			virtual void set_float(const std::string& name, const glm::vec2& value);
			virtual void set_float(const std::string& name, const glm::vec3& value);
			virtual void set_float(const std::string& name, const glm::vec4& value);

			virtual void set_int(const std::string& name, int value);
		public:
			unsigned int ID;
		private:
			unsigned int compile_shader(const char* source, unsigned int type);

		};

		class ShaderLibrary
		{
		public:
			ShaderLibrary() = default;
			void add(const std::string& name, std::shared_ptr<ShaderProgram> program)
			{
				_Shaders[name] = program;
			}

			std::shared_ptr<ShaderProgram> get(const std::string& name)
			{
				return _Shaders[name];
			}

		private:
			std::unordered_map <std::string, std::shared_ptr<ShaderProgram>> _Shaders;
		};

	}
}


#endif