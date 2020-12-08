#pragma once

#include "Graphics/Image/Image.hpp"
#include "Graphics/Vector.hpp"
#include <GL/glew.h>

namespace hlvl
{
namespace texture
{
	class Texture
	{
		using Image = image::Image;
		using Vector2u = vector::Vector2u;

		GLuint gl_id;
		Vector2u size;
	public:
		Texture();
		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		~Texture();

		void setImage(const Image& img);
		inline Vector2u getSize() const {
			return size;
		}

		void activate() const;
		inline GLuint getId() const {
			return gl_id;
		}
		
	};
}
}