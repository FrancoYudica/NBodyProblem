#include "GLShaderProgram.h"
#include <glad/glad.h>
#include <iostream>

using namespace Wolf::Rendering;
using namespace Wolf::Rendering::GL;


GLShaderProgram::GLShaderProgram(const string& vertex_src, const string& fragment_src)
{
	
	// Shader compilation
	unsigned int vertex_shader = compile_shader(vertex_src, GL_VERTEX_SHADER);
	unsigned int fragment_shader = compile_shader(fragment_src, GL_FRAGMENT_SHADER);


	// Creates the program
	ID = glCreateProgram();


	// Attaches the shaders to the program
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);

	// Last step for ShaderProgram
	glLinkProgram(ID);

	// Status test
	int sucess;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &sucess);
	
	if (!sucess)
	{
		glGetShaderInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// once linked, shader can be deleted
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void GLShaderProgram::bind()
{
	glUseProgram(ID);
}

void GLShaderProgram::unbind()
{
	glUseProgram(0);
}

void GLShaderProgram::set_float(const std::string& name, float value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1f(location, value);
}

void GLShaderProgram::set_float(const std::string& name, const glm::vec2& value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform2f(location, value.x, value.y);
}

void GLShaderProgram::set_float(const std::string& name, const glm::vec3& value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void GLShaderProgram::set_float(const std::string& name, const glm::vec4& value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void GLShaderProgram::set_int(const std::string& name, int value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, value);
}

void GLShaderProgram::set_matrix(const string& name, const glm::mat4& matrix) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(location, 1, false, &matrix[0][0]);

}


unsigned int GLShaderProgram::compile_shader(const string& source, unsigned int type)
{

	unsigned int id = glCreateShader(type);
	const char* data = source.c_str();
	glShaderSource(id, 1, &data, NULL);
	glCompileShader(id);

	int sucess;
	char infoLog[512];

	glGetShaderiv(id, GL_COMPILE_STATUS, &sucess);

	if (!sucess)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Sucess in compilation
	return id;

}

std::shared_ptr<ShaderProgram> ShaderProgram::create(const string& vertex_src, const string& fragment_src)
{
    return std::make_shared<GLShaderProgram>(vertex_src, fragment_src);
}
