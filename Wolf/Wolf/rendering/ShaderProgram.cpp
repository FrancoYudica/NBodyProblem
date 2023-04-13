#include "ShaderProgram.h"
#include <glad/glad.h>

using namespace Wolf::Rendering;

ShaderProgram::ShaderProgram(const char* vertex_shader_path, const char* fragment_shader_path)
{
	
	// Shader compilation
	unsigned int vertex_shader = compile_shader(vertex_shader_path, GL_VERTEX_SHADER);
	unsigned int fragment_shader = compile_shader(fragment_shader_path, GL_FRAGMENT_SHADER);


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

void ShaderProgram::bind()
{
	glUseProgram(ID);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

void ShaderProgram::set_float(const std::string& name, float value)
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1f(location, value);
}

void ShaderProgram::set_float(const std::string& name, const glm::vec2& value)
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform2f(location, value.x, value.y);
}

void ShaderProgram::set_float(const std::string& name, const glm::vec3& value)
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::set_float(const std::string& name, const glm::vec4& value)
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::set_int(const std::string& name, int value)
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, value);
}

unsigned int ShaderProgram::compile_shader(const char* source, unsigned int type)
{

	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &source, NULL);
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

