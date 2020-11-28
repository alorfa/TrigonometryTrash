#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include "Graphics/Vector.hpp"
#include "Graphics/Matrix.hpp"

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
		static void use(Shader* shader);

		/*
		* Возвращает location для дальнейшего использования в setUniform.
		* В случае ошибки возвращает -1
		*/
		Uniform getLocation(const char* name);
		void setUniform(Uniform location, float value);
		void setUniform(Uniform location, const Vector3& value);
		void setUniform(Uniform location, const Matrix4& value);

		enum Type
		{
			Vertex, Geometry, Fragment
		};
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
		* Если шейдер не скомпилируется, метод бросит исключение hlvl::shader_error
		* с сообщением ошибки. Если шейдер компилируется, но есть предупреждения,
		* то они запишутся в message, если оно не равно nullptr
		*/
		void loadFromMemory(const char* data, Shader::Type type, std::string* message = nullptr);

		/*
		* Если указанный файл не найден, метод бросит исключение hlvl::file_not_found
		* с названием файла. Иначе метод вызовет \ref loadFromMemory с содержимым файла
		*/
		void loadFromFile(const char* filename, Shader::Type type, std::string* message = nullptr);

		/*
		* Линкует шейдеры в шейдерную программу. При ошибке линковки бросает исключение
		* hlvl::shader_error с сообщением об ошибке. Если шейдер успешно линкуется, но
		* есть предупреждения, они запишутся в message, если оно не равно nullptr
		*/
		Shader link(std::string* message = nullptr);
	};


}
}