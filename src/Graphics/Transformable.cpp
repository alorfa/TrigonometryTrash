#include <Graphics/Transformable.hpp>
#include <glm/gtx/transform.hpp>

#include "header.hpp"

using namespace hlvl::matrix;
using namespace hlvl::vector;

#ifdef H_DEBUG
std::ostream& operator<<(std::ostream& out, const glm::mat2& matrix)
{
	out << "[" << matrix[0][0] << ", " << matrix[0][1] << "]" << std::endl
		<< "[" << matrix[1][0] << ", " << matrix[1][1] << "]" << std::endl;

	return out;
}
std::ostream& operator<<(std::ostream& out, const glm::mat4& matrix)
{
	out << "[" << matrix[0][0] << ", " << matrix[0][1] << ", "
		<< matrix[0][2] << ", " << matrix[0][3] << "]" << std::endl
		<< "[" << matrix[1][0] << ", " << matrix[1][1] << ", "
		<< matrix[1][2] << ", " << matrix[1][3] << "]" << std::endl
		<< "[" << matrix[2][0] << ", " << matrix[2][1] << ", "
		<< matrix[2][2] << ", " << matrix[2][3] << "]" << std::endl
		<< "[" << matrix[3][0] << ", " << matrix[3][1] << ", "
		<< matrix[3][2] << ", " << matrix[3][3] << "]" << std::endl;

	return out;
}std::ostream& operator<<(std::ostream& out, const glm::mat3& matrix)
{
	out << "[" << matrix[0][0] << ", " << matrix[0][1] << ", "
		<< matrix[0][2] << "]" << std::endl
		<< "[" << matrix[1][0] << ", " << matrix[1][1] << ", "
		<< matrix[1][2] << "]" << std::endl
		<< "[" << matrix[2][0] << ", " << matrix[2][1] << ", "
		<< matrix[2][2] << "]" << std::endl;

	return out;
}
std::ostream& operator<<(std::ostream& out, const glm::vec2& vector)
{
	out << "[" << vector.x << ", " << vector.y << "]" << std::endl;
	return out;
}
#endif //H_DEBUG

namespace hlvl
{
namespace transform
{
//////////////////////Transform//////////////////////
	Transform::Transform()
		: position(), scale(1.f, 1.f), rotation(0.f) {}

	Transform::Transform(const Vector2& position, const Vector2& scale, float rotation)
		: position(position), scale(scale), rotation(rotation) {}

	void Transform::setTransform(const Transform& other)
	{
		position = other.position;
		scale = other.scale;
		rotation = other.rotation;
	}

	//////////////////////Transformable//////////////////////
	Transformable::Transformable()
		: transform() {}

	Transformable::Transformable(const Vector2& position, const Vector2& scale, float rotation)
		: transform(position, scale, rotation) {}

	Transformable::Transformable(const Transform& other)
		: transform(other) {}

	//////////////////////position//////////////////////
	void Transformable::setPosition(float x, float y)
	{
		transform.position.x = x;
		transform.position.y = y;
		matrix_need_update = true;
	}
	void Transformable::setPosition(const Vector2& xy)
	{
		setPosition(xy.x, xy.y);
	}
	void Transformable::move(float x, float y)
	{
		setPosition(
			transform.position.x + x,
			transform.position.y + y);
	}
	void Transformable::move(const Vector2& xy)
	{
		move(xy.x, xy.y);
	}
	const Vector2& Transformable::getPosition() const
	{
		return transform.position;
	}

	//////////////////////rotation//////////////////////
	void Transformable::setRotationRad(float radian)
	{
		transform.rotation = radian;
		matrix_need_update = true;
	}
	void Transformable::setRotationDeg(float degrees)
	{
		setRotationRad(glm::radians(degrees));
	}
	void Transformable::rotateRad(float radian)
	{
		setRotationRad(transform.rotation + radian);
	}
	void Transformable::rotateDeg(float degrees)
	{
		rotateRad(glm::radians(degrees));
	}
	void Transformable::rotateRadOP(float radian, const Vector2& center)
	{
		float sine = sin(radian);
		float cosine = cos(radian);
		move(center.x * (1.f - cosine) + center.y * sine,
			center.y * (1.f - cosine) - center.x * sine);
	}
	void Transformable::rotateDegOP(float degrees, const Vector2& center)
	{
		rotateRadOP(glm::radians(degrees), center);
	}
	void Transformable::rotateRad(float radian, const Vector2& center)
	{
		setRotationRad(transform.rotation + radian);
		rotateRadOP(radian, center);
	}
	void Transformable::rotateDeg(float degrees, const Vector2& center)
	{
		rotateRad(glm::radians(degrees), center);
	}
	float Transformable::getRotation() const
	{
		return transform.rotation;
	}

	//////////////////////scale//////////////////////
	void Transformable::setScale(float x, float y)
	{
		transform.scale.x = x;
		transform.scale.y = y;
		matrix_need_update = true;
	}
	void Transformable::setScale(const Vector2& xy)
	{
		setScale(xy.x, xy.y);
	}
	void Transformable::scale(float x, float y)
	{
		setScale(
			transform.scale.x * x,
			transform.scale.y * y);
	}
	void Transformable::scale(const Vector2& xy)
	{
		scale(xy.x, xy.y);
	}
	void Transformable::scale(const Vector2& xy, const Vector2& center)
	{
		scale(xy.x, xy.y);
		scaleOP(xy, center);
	}
	void Transformable::scaleOP(const Vector2& xy, const Vector2& center)
	{
		move(center.x * (1.f - xy.x),
			center.x * (1.f - xy.y));
	}
	const Vector2& Transformable::getScale() const
	{
		return transform.scale;
	}

	void Transformable::setTransform(const Transform& other)
	{
		transform.position = other.position;
		transform.scale = other.scale;
		transform.rotation = other.rotation;

		matrix_need_update = true;
	}
	const Transform& Transformable::getTransform() const
	{
		return transform;
	}

	//////////////////////matrix//////////////////////
	Matrix4& Transformable::getMatrix() const
	{
		if (matrix_need_update)
		{
			float cosine = cos(transform.rotation);
			float sine = sin(transform.rotation);
			float scalxc = transform.scale.x * cosine;
			float scalyc = transform.scale.y * cosine;
			float scalxs = transform.scale.x * sine;
			float scalys = transform.scale.y * sine;
			float tx = transform.position.x;
			float ty = transform.position.y;

			matrix = glm::mat4(
				scalxc,	-scalxs,	0.f, 0.f,
				scalys,	scalyc,		0.f, 0.f,
				0.f,		0.f,	1.f, 0.f,
				tx,		ty,			0.f, 1.f);
		}
		matrix_need_update = false;

		return matrix;
	}


}
}