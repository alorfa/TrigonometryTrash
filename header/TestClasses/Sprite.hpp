#pragma once

#include "Graphics/Image/Texture.hpp"
#include "Graphics/Buffer.hpp"
#include "Graphics/Transformable.hpp"
#include "Graphics/Vector.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Drawable.hpp"
#include "Graphics/Shader.hpp"

namespace sprite
{
	using namespace hlvl::texture;
	using namespace hlvl::buffer;
	using namespace hlvl::transform;
	using namespace hlvl::vector;
	using namespace hlvl::drawable;
	using namespace hlvl::camera;
	using namespace hlvl::shader;

	// if you set a texture and it was deleted, sprite не сможет корректно работать
	class Sprite : public Transformable, public Drawable
	{
		const Texture* texture = nullptr;

		VertexBuffer points{0};
		TexCoordsBuffer UV_buffer{2};
		IndexBuffer indexes;
	public:
		Sprite()
		{
			points.setData({
				{-1.f, -1.f},
				{1.f, -1.f},
				{1.f, 1.f},
				{-1.f, 1.f}
			});
			UV_buffer.setData({
				{0.f, 1.f},
				{1.f, 1.f},
				{1.f, 0.f},
				{0.f, 0.f}
			});
			indexes.setData({
				0, 2, 1,
				0, 2, 3
			});
			indexes.updateData();
			UV_buffer.updateData();
			points.updateData();
		}
		Sprite(const Sprite&) = default;
		Sprite& operator=(const Sprite&) = default;
		~Sprite() = default;

		void draw(const CameraBase& camera) const override
		{
			auto mvp = camera.getMatrix() * this->getMatrix();

			const Shader& shader = Shader::getShader(Shader::TexturedVertexes);

			shader.use();
			shader.setUniform(shader.getLocation("transform"), mvp);
			texture->activate();
			shader.setUniform(shader.getLocation("img"), *texture);

			points.activate();
			UV_buffer.activate();

			indexes.activate();
			indexes.drawArrays();

			UV_buffer.deactivate();
			points.deactivate();
		}

		void setTexture(const Texture& t)
		{
			this->texture = &t;
		}

		void setTextureRect(Vector2u left_up_pixel, Vector2u right_down_pixel)
		{
			float left_x, right_x, down_y, up_y;
			left_x = (float)left_up_pixel.x / (float)texture->getSize().x;
			right_x = (float)right_down_pixel.x / (float)texture->getSize().x;
			down_y = (float)right_down_pixel.y / (float)texture->getSize().y;
			up_y = (float)left_up_pixel.y / (float)texture->getSize().y;

			UV_buffer.setData({
				{left_x, down_y},
				{right_x, down_y},
				{right_x, up_y},
				{left_x, up_y},
			});
			UV_buffer.updateData();
		}
	};
}