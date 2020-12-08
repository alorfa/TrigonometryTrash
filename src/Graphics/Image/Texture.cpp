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
	/*
	Texture::Texture(Texture&& other)
	{
		// destroy previous object(include texture id)
		this->~Texture();

		// copy data of other texture
		size = other.size;
		gl_id = other.gl_id;
	}
	Texture& Texture::operator=(Texture&& other)
	{

	}/**/
	Texture::~Texture()
	{
		if (gl_id)
			glDeleteTextures(1, &gl_id);
	}

	void Texture::setImage(const Image& img)
	{
		this->size = img.getSize();

		glBindTexture(GL_TEXTURE_2D, gl_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			(GLsizei)img.getSize().x, (GLsizei)img.getSize().y,
			0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)img.getPixels());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, -10.f);
	}
	void Texture::activate() const
	{
		glActiveTexture(GL_TEXTURE0 + gl_id);
		glBindTexture(GL_TEXTURE_2D, gl_id);
	}
}
}