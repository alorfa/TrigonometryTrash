#pragma once

#include <exception>
#include <string>

namespace hlvl
{
	class exception : public std::exception {};

	class file_not_found : public exception
	{
	public:
		const std::string filename;
		file_not_found(const std::string& filename);
	};
	class shader_error : public exception
	{
	public:
		const std::string message;
		shader_error(const std::string& message);
	};
}