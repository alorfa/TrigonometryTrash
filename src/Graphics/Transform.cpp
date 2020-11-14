#include <Graphics/Transform.hpp>
#include <glm/gtx/transform.hpp>

#include "header.hpp"

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


void Transform3D::move(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.x += z;
}
void Transform3D::move(const Vector3& xyz)
{
	position += xyz;
}
void Transform3D::rotateRad(float x, float y, float z)
{
	rotation.x += x;
	rotation.y += y;
	rotation.z += z;
}
void Transform3D::rotateRad(const Vector3& xyz)
{
	rotateRad(xyz.x, xyz.y, xyz.z);
}
void Transform3D::rotateDeg(float x, float y, float z)
{
	rotateRad(glm::radians(x), glm::radians(x), glm::radians(x));
}
void Transform3D::rotateDeg(const Vector3& xyz)
{
	rotateRad(glm::radians(xyz));
}
void Transform3D::scale(float x, float y, float z)
{
	scope.x += x;
	scope.y += y;
	scope.x += z;
}
void Transform3D::scale(const Vector3& xyz)
{
	scope += xyz;
}
const Matrix4& Transform3D::convertToMatrix() const
{
	glm::mat4 pos = glm::translate(glm::mat4(1.f), position);
	glm::mat4 rot{
		{1.f, 0.f,				0.f,				0.f},
		{0.f, cos(rotation.x),	-sin(rotation.x),	0.f},
		{0.f, sin(rotation.x),	cos(rotation.x),	0.f},
		{0.f, 0.f,				0.f,				1.f}
	};
	rot *= glm::mat4{
		{cos(rotation.y),	0.f, sin(rotation.y),	0.f},
		{0.f,				1.f, 0.f,				0.f},
		{-sin(rotation.y),	0.f, cos(rotation.y),	0.f},
		{0.f,				0.f, 0.f,				1.f}
	};
	rot *= glm::mat4{
		{cos(rotation.z),	-sin(rotation.z),	0.f, 0.f},
		{sin(rotation.z),	cos(rotation.z),	0.f, 0.f},
		{0.f,				0.f,				1.f, 0.f},
		{0.f,				0.f,				0.f, 1.f}
	};
	glm::mat4 scal = glm::scale(scope);
	return matrix;
}

Transform2D::Transform2D()
	: position(), scope(1.f, 1.f), rotation(0.f) {}

//////////////////////position//////////////////////
void Transform2D::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	matrix_need_update = true;
}
void Transform2D::setPosition(const Vector2& xy)
{
	setPosition(xy.x, xy.y);
}
void Transform2D::move(float x, float y)
{
	setPosition(position.x + x, position.y + y);
}
void Transform2D::move(const Vector2& xy)
{
	move(xy.x, xy.y);
}
const Vector2& Transform2D::getPosition() const
{
	return position;
}

//////////////////////rotation//////////////////////
void Transform2D::setRotationRad(float radian)
{
	rotation = radian;
	matrix_need_update = true;
}
void Transform2D::setRotationDeg(float degrees)
{
	setRotationRad(glm::radians(degrees));
}
void Transform2D::rotateRad(float radian)
{
	setRotationRad(rotation + radian);
}
void Transform2D::rotateDeg(float degrees)
{
	rotateRad(glm::radians(degrees));
}
void Transform2D::rotateRadOP(float radian, const Vector2& center)
{
	float sine = sin(radian);
	float cosine = cos(radian);
	move(center.x * (1.f - cosine) + center.y * sine,
		center.y * (1.f - cosine) - center.x * sine);
}
void Transform2D::rotateDegOP(float degrees, const Vector2& center)
{
	rotateRadOP(glm::radians(degrees), center);
}
void Transform2D::rotateRad(float radian, const Vector2& center)
{
	setRotationRad(rotation + radian);
	rotateRadOP(radian, center);
}
void Transform2D::rotateDeg(float degrees, const Vector2& center)
{
	rotateRad(glm::radians(degrees), center);
}
float Transform2D::getRotation() const
{
	return rotation;
}

//////////////////////scale//////////////////////
void Transform2D::setScale(float x, float y)
{
	scope.x = x;
	scope.y = y;
	matrix_need_update = true;
}
void Transform2D::setScale(const Vector2& xy)
{
	setScale(xy.x, xy.y);
}
void Transform2D::scale(float x, float y)
{
	setScale(scope.x * x, scope.y * y);
}
void Transform2D::scale(const Vector2& xy)
{
	scale(xy.x, xy.y);
}
void Transform2D::scale(const Vector2& xy, const Vector2& center)
{
	scale(xy.x, xy.y);
	scaleOP(xy, center);
}
void Transform2D::scaleOP(const Vector2& xy, const Vector2& center)
{
	move(center.x * (1.f - xy.x),
		center.x * (1.f - xy.y));
}
const Vector2& Transform2D::getScale() const
{
	return scope;
}

//////////////////////matrix//////////////////////
const Matrix4& Transform2D::convertToMatrix() const
{
	if (matrix_need_update)
	{
		float cosine = cos(rotation);
		float sine = sin(rotation);
		float scalxc = scope.x + cosine;
		float scalyc = scope.y + cosine;
		float scalxs = scope.x + sine;
		float scalys = scope.y + sine;
		float tx = position.x;
		float ty = position.y;

		matrix = glm::mat4(
			{scalxc, scalxs, 0.f, tx},
			{scalys, scalyc, 0.f, ty},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f});
	}
	matrix_need_update = false;

	return matrix;
}


}
}