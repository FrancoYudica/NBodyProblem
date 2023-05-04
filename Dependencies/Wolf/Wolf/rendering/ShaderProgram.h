#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include <string>
#include <unordered_map>
#include <iostream>
#include <glm/glm.hpp>
#include <memory>
#include "../utils/PathManager.h"
#include "../utils/File.h"

using std::string;

namespace Wolf
{
	namespace Rendering
	{
		class ShaderProgram
		{

		public:
			ShaderProgram() = default;
			virtual void bind() = 0;
			virtual void unbind() = 0;
			virtual void set_float(const string& name, float value) const = 0;
			virtual void set_float(const string& name, const glm::vec2& value) const = 0;
			virtual void set_float(const string& name, const glm::vec3& value) const = 0;
			virtual void set_float(const string& name, const glm::vec4& value) const = 0;
			virtual void set_int(const string& name, int value) const = 0;
			virtual void set_matrix(const string& name, const glm::mat4& matrix) const = 0;
			static std::shared_ptr<ShaderProgram> create(const string& vertex_src, const string& fragment_src);

			static std::shared_ptr<ShaderProgram> create(
				const Wolf::Path& vertex_path,
				const Wolf::Path& fragment_path)
			{
				
				if (!vertex_path.exists())
				{
					std::cout << "ERROR: ShaderProgram::create. Vertex path doesn't exist" << std::string(vertex_path) << std::endl;
				}
				if (!fragment_path.exists())
				{
					std::cout << "ERROR: ShaderProgram::create. Fragment path doesn't exist" << std::string(fragment_path) << std::endl;
				}

				auto vertex_file = Wolf::File(vertex_path);
				auto fragment_file = Wolf::File(fragment_path);
				return create(
					vertex_file.read(), 
					fragment_file.read()
				);
			}
		};

		class ShaderLibrary
		{
		public:
			ShaderLibrary() = default;
			void add(const string& name, const std::shared_ptr<ShaderProgram>& program)
			{
				_shaders[name] = program;
			}

			std::shared_ptr<ShaderProgram> get(const string& name)
			{
				return _shaders[name];
			}

		private:
			std::unordered_map <string, std::shared_ptr<ShaderProgram>> _shaders;
		};

	}
}


#endif