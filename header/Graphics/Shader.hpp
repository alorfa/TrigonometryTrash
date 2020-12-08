#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include "Graphics/Vector.hpp"
#include "Graphics/Matrix.hpp"
#include "Graphics/Image/Texture.hpp"

using namespace hlvl::vector;
using namespace hlvl::matrix;

namespace hlvl
{
namespace shader
{
	typedef GLint Uniform;

	class ShaderCompiler;

	class Shader
	{
		friend class ShaderCompiler;

		using Texture = texture::Texture;

		GLuint shader_prog;

		Shader(GLuint program_id);
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
	public:
		Shader();
		Shader(Shader&& other) noexcept;
		Shader& operator=(Shader&& other) noexcept;
		~Shader();

		GLuint getNativeHandle() const;

		/* Uses the shader. If it is nullptr then shader unbind*/
		void use() const;

		/*
		* ���������� location ��� ����������� ������������� � setUniform.
		* � ������ ������ ���������� -1
		*/
		Uniform getLocation(const char* name) const;
		void setUniform(Uniform location, float value) const;
		void setUniform(Uniform location, const Vector3& value) const;
		void setUniform(Uniform location, const Matrix4& value) const;
		void setUniform(Uniform location, const Texture& texture) const;

		enum Type
		{
			Vertex, Geometry, Fragment
		};
		enum Inbuilt
		{
			TexturedVertexes,
			ColoredVertexes
		};

		static const Shader& getShader(Inbuilt shader);
	};
	class ShaderCompiler
	{
		GLuint vertex, fragment, geometry;

		void deltete_shaders();

		GLuint load_from_memory(const char* shader_source, GLenum shader_type, std::string* message);
	public:
		ShaderCompiler();
		~ShaderCompiler();

		/*
		* ���� ������ �� ��������������, ����� ������ ���������� hlvl::shader_error
		* � ���������� ������. ���� ������ �������������, �� ���� ��������������,
		* �� ��� ��������� � message, ���� ��� �� ����� nullptr
		*/
		void loadFromMemory(const char* data, Shader::Type type, std::string* message = nullptr);

		/*
		* ���� ��������� ���� �� ������, ����� ������ ���������� hlvl::file_not_found
		* � ��������� �����. ����� ����� ������� \ref loadFromMemory � ���������� �����
		*/
		void loadFromFile(const char* filename, Shader::Type type, std::string* message = nullptr);

		/*
		* ������� ������� � ��������� ���������. ��� ������ �������� ������� ����������
		* hlvl::shader_error � ���������� �� ������. ���� ������ ������� ���������, ��
		* ���� ��������������, ��� ��������� � message, ���� ��� �� ����� nullptr
		*/
		Shader link(std::string* message = nullptr);
	};


}
}