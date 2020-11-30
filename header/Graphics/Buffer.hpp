#pragma once

#include <GL/glew.h>
#include <vector>
#include "Graphics/Vector.hpp"

#include "header.hpp"

using namespace hlvl::vector;

namespace hlvl
{
namespace buffer
{

	template <typename T>
	class Buffer
	{
	protected:
		GLuint buf = 0;
		std::vector<T> data;
	private:
		void delete_id()
		{
			if (buf)
				glDeleteBuffers(1, &buf);
			buf = 0;
		}
		void create_id()
		{
			delete_id();
			glGenBuffers(1, &buf);
		}
	public:
		Buffer()
		{
			create_id();
		}
		Buffer(const Buffer& other)
		{
			create_id();

			data = other.data;
		}
		Buffer(Buffer&& other)
		{
			operator=(other);
		}
		Buffer& operator=(const Buffer& other)
		{
			data = other.data;

			return *this;
		}
		Buffer& operator=(Buffer&& other)
		{
			buf = other.buf;
			data = std::move(other.data);

			other.buf = 0;

			PRINT(other.data.empty());

			return *this;
		}
		Buffer& operator=(const std::vector<T>& vector)
		{
			data = vector;

			return *this;
		}
		Buffer& operator=(std::vector<T>&& vector)
		{
			data = std::move(vector);

			return *this;
		}
		Buffer& operator+=(const T& new_elem)
		{
			data.push_back(new_elem);

			return *this;
		}
		Buffer& operator+=(const std::vector<T>& v)
		{
			auto prev_size = data.size();
			auto new_size = prev_size + v.size();
			data.resize(new_size);
			for (size_t i = 0; i < v.size(); i++)
				data[i + prev_size] = v[i];

			return *this;
		}
		~Buffer()
		{
			delete_id();
		}

		void reserve(size_t size)
		{
			data.reserve(size);
		}
		void resize(size_t size)
		{
			data.resize(size);
		}
		void add(const T& new_elem)
		{
			data.push_back(new_elem);
		}
		void add(const std::vector<T>& v)
		{
			operator+=(v);
		}
	};

	template <typename T, int components_count, GLenum type>
	class DrawableBuffer : public Buffer<T>
	{
	public:
		DrawableBuffer()
		{
			attribute = 0;
		}
		DrawableBuffer(GLuint attribute)
		{
			this->attribute = attribute;
		}

		GLuint attribute;

		void updateData()
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->buf);
			glBufferData(GL_ARRAY_BUFFER, this->data.size() * sizeof(T), &this->data[0], GL_STATIC_DRAW);
		}
		void activate()
		{
			glEnableVertexAttribArray(attribute);
			glBindBuffer(GL_ARRAY_BUFFER, this->buf);
			glVertexAttribPointer(attribute, components_count, type, GL_FALSE, 0, nullptr);
		}
		void deactivate()
		{
			glDisableVertexAttribArray(attribute);
		}
	};

	template <typename T>
	class IndexBuffer : public Buffer<T>
	{
	public:
		void updateData()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buf);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->data.size() * sizeof(T), &this->data[0], GL_STATIC_DRAW);
		}
	};

	using VertexBuffer = DrawableBuffer<Vector2, 2, GL_FLOAT>;

	using ColorBuffer3f = DrawableBuffer<Color3f, 3, GL_FLOAT>;
	using ColorBuffer4f = DrawableBuffer<Color4f, 4, GL_FLOAT>;
	using ColorBuffer3b = DrawableBuffer<Color3b, 3, GL_BYTE>;
	using ColorBuffer4b = DrawableBuffer<Color4b, 4, GL_BYTE>;

	using TexCoordsBuffer = DrawableBuffer<Vector2, 2, GL_FLOAT>;
}
}