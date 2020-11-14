#include "System/exception.hpp"

namespace hlvl
{
	file_not_found::file_not_found(const std::string& message)
		: filename(message) {}

	shader_error::shader_error(const std::string& message)
		: message(message) {}
}