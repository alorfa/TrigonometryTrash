#pragma once

#include "Graphics/Image/Texture.hpp"
#include <GL/glew.h>
//#include <GL/GL.h>

namespace hlvl
{
namespace texture
{
	Texture::Texture()
	{
		glGenTextures(1, &gl_id);
	}
	Texture::~Texture()
	{
		glDeleteTextures(1, &gl_id);
	}

	void Texture::setImage(const Image& img)
	{
		glBindTexture(GL_TEXTURE_2D, gl_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			(GLsizei)img.getSize().x, (GLsizei)img.getSize().y,
			0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)img.getPixels());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	void Texture::activate()
	{
		glActiveTexture(GL_TEXTURE0 + gl_id);
		glBindTexture(GL_TEXTURE_2D, gl_id);
	}
}
}