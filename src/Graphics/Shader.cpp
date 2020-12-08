#include "Graphics/Shader.hpp"
#include <fstream>
#include "System/exception.hpp"
#include "header.hpp"

namespace shader_sources
{
	static const char* textured_vertexes_vert =
		"#version 330\n"

		"layout(location = 0) in vec2 input_pos;"
		"layout(location = 2) in vec2 input_UV;"

		"out vec2 frag_UV;"

		"uniform mat4 transform;"

		"void main()"
		"{"
		"	gl_Position = transform * vec4(input_pos, 0, 1);"
		"	frag_UV = input_UV;"
		"}";

	static const char* textured_vertexes_frag =
		"#version 330\n"

		"in vec2 frag_UV;"

		"uniform sampler2D img;"

		"out vec4 color;"

		"void main()"
		"{"
		"	color = texture(img, frag_UV);"
		"}";

	static const char* colored_vertexes_vert =
		"#version 330\n"

		"layout(location = 0) in vec2 input_pos;"
		"layout(location = 1) in vec3 input_color;"

		"out vec3 fragment_color;"

		"uniform mat4 transform;"

		"void main()"
		"{"
		"	gl_Position = transform * vec4(input_pos, 0, 1);"
		"	fragment_color = input_color;"
		"}";

	static const char* colored_vertexes_frag =
		"#version 330\n"

		"in vec3 fragment_color;"

		"out vec4 color;"

		"void main()"
		"{"
		"	color = vec4(fragment_color, 1);"
		"}";
}

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
	void Shader::use() const
	{
		glUseProgram(this->shader_prog);
	}
	Uniform Shader::getLocation(const char* name) const
	{
		return glGetUniformLocation(shader_prog, name);
	}
	void Shader::setUniform(Uniform location, float value) const
	{
		glUniform1f(location, value);
	}
	void Shader::setUniform(Uniform location, const Vector3& value) const
	{
		glUniform3f(location, value.x, value.y, value.z);
	}
	void Shader::setUniform(Uniform location, const Matrix4& value) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)& value);
	}
	void Shader::setUniform(Uniform location, const Texture& texture) const
	{
		glUniform1i(location, texture.getId());
	}

	const Shader& Shader::getShader(Inbuilt shader)
	{
		static Shader
			textured_vertexes, colored_vertexes;

		static bool first_call = true;
		if (first_call)
		{
			first_call = false;

			ShaderCompiler compiler;
			using namespace shader_sources;

			compiler.loadFromMemory(textured_vertexes_vert, Type::Vertex);
			compiler.loadFromMemory(textured_vertexes_frag, Type::Fragment);
			textured_vertexes = compiler.link();

			compiler.loadFromMemory(colored_vertexes_vert, Type::Vertex);
			compiler.loadFromMemory(colored_vertexes_frag, Type::Fragment);
			colored_vertexes = compiler.link();
		}

		switch (shader)
		{
		case Inbuilt::TexturedVertexes:
			return textured_vertexes;
		case Inbuilt::ColoredVertexes:
			return colored_vertexes;
		}
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
				throw shader_error(shader_message.c_str());
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
				throw shader_error(error.c_str());
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