#include "System/exception.hpp"

namespace hlvl
{
	file_not_found::file_not_found(const char* message)
		: filename(message) {}

	shader_error::shader_error(const char* message)
		: message(message) {}

	image_error::image_error(const char* message)
		: message(message) {}
}