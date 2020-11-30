#include "Graphics/Image/Image.hpp"
#include "System/exception.hpp"

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

	void Image::create(Vector2u size, const byte* data)
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

	void Image::loadFromFile(const char* filename)
	{
		int width = 0;
		int height = 0;
		int channels = 0;
		byte* new_data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

		if (new_data)
		{
			create(Vector2u(width, height), new_data);

			stbi_image_free(new_data);
		}
		else
		{
			throw image_error(stbi_failure_reason());
		}


	}
	void Image::loadFromMemory(const byte* data, size_t size)
	{
		if (data && size)
		{
			int width = 0;
			int height = 0;
			int channels = 0;
			byte* new_data = stbi_load_from_memory(data, (int)size, &width, &height, &channels, STBI_rgb_alpha);

			if (new_data)
			{
				create(Vector2u(width, height), new_data);

				stbi_image_free(new_data);
			}
			else
			{
				throw image_error(stbi_failure_reason());
			}
		}
		else
		{
			throw image_error("Uncorrect data!");
		}
	}

	void Image::setPixel(Vector2u pos, const Color4b& color) 
	{
		pixels[pos.x + pos.y * size.x] = color;
	}

	Vector2u Image::getSize() const
	{
		return size;
	}
	const Color4b& Image::getPixel(Vector2u pos) const
	{
		return pixels[pos.x + pos.y * size.x];
	}
	const Color4b* Image::getPixels() const
	{
		return pixels.data();
	}
	Color4b& Image::getPixel(Vector2u pos)
	{
		return pixels[pos.x + pos.y * size.x];
	}
	Color4b* Image::getPixels()
	{
		return pixels.data();
	}

}
}