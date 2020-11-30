#pragma once

#include "Graphics/Image/Image.hpp"
#include <GL/glew.h>

namespace hlvl
{
namespace texture
{
	class Texture
	{
		using Image = image::Image;

		GLuint gl_id;
	public:
		Texture();
		~Texture();

		void setImage(const Image& img);

		void activate();
		inline GLuint getId() const {
			return gl_id;
		}
		
	};
}
}