#pragma once

#include "Graphics/Vector.hpp"
#include <vector>

namespace hlvl
{
namespace image
{

	class Image
	{
		using byte = unsigned char;
		using Vector2u = vector::Vector2u;
		using Color4b = vector::Color4b;

		Vector2u size;
		std::vector<Color4b> pixels;
	public:
		Image() = default;
		~Image() = default;
		Image(const Image& other) = default;
		Image& operator=(const Image& other) = default;
		Image(Image&& other);
		Image& operator=(Image&& other);

		void create(Vector2u size, const byte* data);
		void create(Vector2u size, const Color4b& fill);

		void loadFromFile(const char* filename);
		void loadFromMemory(const byte* data, size_t size);

		void setPixel(Vector2u pos, const Color4b& color);
		
		Vector2u getSize() const;
		const Color4b* getPixels() const;
		const Color4b& getPixel(Vector2u pos) const;

		Color4b* getPixels();
		Color4b& getPixel(Vector2u pos);
	};

}
}