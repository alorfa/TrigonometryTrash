#include "Graphics/Image/Image.hpp"

#include <stb/stb_image.h>

using namespace hlvl::vector;

namespace hlvl
{
namespace image
{
	Image::Image(Image&& other)
	{
		size = other.size;
		pixels = std::move(other.pixels);

		other.size = Vector2u();
	}
	Image& Image::operator=(Image&& other)
	{
		size = other.size;
		pixels = std::move(other.pixels);

		other.size = Vector2u();

		return *this;
	}

	void Image::create(Vector2u size, byte* data)
	{
		this->size = size;

		if (size.x && size.y)
		{
			pixels.assign((Color4b*)data, (Color4b*)data + (size.x * size.y));
		}
		else
		{
			pixels.clear();
		}
	}
	void Image::create(Vector2u size, const Color4b& fill)
	{
		this->size = size;

		if (size.x && size.y)
		{
			pixels.resize(size.x * size.y);

			for (size_t i = 0; i < pixels.size(); i++)
				pixels[i] = fill;
		}
		else
		{
			pixels.clear();
		}
	}

	void Image::setPixel(Vector2u pos, const Color4b& color)
	{
		pixels[pos.x + pos.y * size.x] = color;
	}
	Color4b Image::getPixel(Vector2u pos)
	{
		return pixels[pos.x + pos.y * size.x];
	}
	Vector2u Image::getSize()
	{
		return size;
	}
	Color4b* Image::getPixels()
	{
		return pixels.data();
	}

}
}