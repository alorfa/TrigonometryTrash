#include "Graphics/Shader.hpp"
#include <fstream>
#include "System/exception.hpp"
#include "header.hpp"

namespace hlvl
{
namespace shader
{


Shader::Shader()
	: shader_prog(0) {}

Shader::Shader(GLuint program_id)
	: shader_prog(program_id) {}

Shader::Shader(Shader&& other) noexcept
	: shader_prog(other.shader_prog)
{
	other.shader_prog = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	shader_prog = other.shader_prog;
	other.shader_prog = 0;
	return *this;
}
Shader::~Shader()
{
	if (shader_prog)
		glDeleteProgram(shader_prog);
}

GLuint Shader::getNativeHandle() const
{
	return shader_prog;
}
void Shader::use(Shader* shader)
{
	if (shader)
		glUseProgram(shader->shader_prog);
	else
		glUseProgram(0);
}
Uniform Shader::getLocation(const char* name)
{
	return glGetUniformLocation(shader_prog, name);
}
void Shader::setUniform(Uniform location, float value)
{
	glUniform1f(location, value);
}
void Shader::setUniform(Uniform location, const Vector3& value)
{
	glUniform3f(location, value.x, value.y, value.z);
}
void Shader::setUniform(Uniform location, const Matrix4& value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)& value);
}

ShaderCompiler::ShaderCompiler()
	: vertex(0), geometry(0), fragment(0) {}

void ShaderCompiler::deltete_shaders()
{
	if (vertex)
		glDeleteShader(vertex);
	if (fragment)
		glDeleteShader(fragment);
	if (geometry)
		glDeleteShader(geometry);
	vertex = geometry = fragment = 0;
}
GLuint ShaderCompiler::load_from_memory(const char* shader_source, GLenum type, std::string* message)
{
	GLuint shader_id = glCreateShader(type);

	glShaderSource(shader_id, 1, &shader_source, nullptr);
	glCompileShader(shader_id);

	GLint log_length = 0;
	GLint compile_status = GL_FALSE;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

	if (log_length > 0)
	{
		if (compile_status == GL_FALSE)
		{
			std::string shader_message;
			shader_message.resize(log_length);
			glGetShaderInfoLog(shader_id, log_length, nullptr, &shader_message[0]);
			throw shader_error(shader_message);
		}
		if (message)
		{
			message->resize(log_length);
			glGetShaderInfoLog(shader_id, log_length, nullptr, &(*message)[0]);
		}
	}
	return shader_id;
}
void ShaderCompiler::loadFromMemory(const char* data, Shader::Type type, std::string* message)
{
	switch (type)
	{
	case Shader::Vertex:
		vertex = load_from_memory(data, GL_VERTEX_SHADER, message);
		break;
	case Shader::Geometry:
		geometry = load_from_memory(data, GL_GEOMETRY_SHADER, message);
		break;
	case Shader::Fragment:
		fragment = load_from_memory(data, GL_FRAGMENT_SHADER, message);
		break;
	}
}
void ShaderCompiler::loadFromFile(const char* filename, Shader::Type type, std::string* message)
{
	std::string input;
	std::ifstream file(filename, std::ios_base::binary);
	if (file.is_open())
	{
		file.seekg(0, std::ios_base::end);
		std::streamsize size = file.tellg();
		if (size > 0)
		{
			file.seekg(0, std::ios_base::beg);
			input.resize(size);
			file.read(&input[0], size);
		}
		input.push_back('\0');
	}
	else
	{
		throw file_not_found(filename);
	}
	loadFromMemory(input.c_str(), type, message);
}
Shader ShaderCompiler::link(std::string* message)
{
	GLuint out_shader = glCreateProgram();

	if (vertex)
		glAttachShader(out_shader, vertex);
	if (fragment)
		glAttachShader(out_shader, fragment);
	if (geometry)
		glAttachShader(out_shader, geometry);
	glLinkProgram(out_shader);

	GLint log_length = 0;
	GLint link_status = GL_FALSE;
	glGetProgramiv(out_shader, GL_INFO_LOG_LENGTH, &log_length);
	glGetProgramiv(out_shader, GL_LINK_STATUS, &link_status);

	if (log_length > 0)
	{
		if (link_status == GL_FALSE)
		{
			std::string error;
			error.resize(log_length);
			glGetProgramInfoLog(out_shader, log_length, nullptr, &error[0]);
			throw shader_error(error);
		}
		if (message)
		{
			message->resize(log_length);
			glGetProgramInfoLog(out_shader, log_length, nullptr, &(*message)[0]);
		}
	}

	if (vertex)
		glDetachShader(out_shader, vertex);
	if (fragment)
		glDetachShader(out_shader, fragment);
	if (geometry)
		glDetachShader(out_shader, geometry);

	deltete_shaders();

	return Shader(out_shader);
}
ShaderCompiler::~ShaderCompiler()
{
	deltete_shaders();
}


}
}