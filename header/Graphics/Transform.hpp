#pragma once

#include <Graphics/Matrix.hpp>
#include <Graphics/Vector.hpp>
#include <memory>

using namespace hlvl::vector;
using namespace hlvl::matrix;

namespace hlvl
{
namespace transform
{


class Transform3D
{
	mutable Matrix4 matrix;

	Vector3 position;
	Vector3 scope;
	Vector3 rotation;
public:

	void move(float x, float y, float z);
	void move(const Vector3& xyz);

	void rotateRad(float x, float y, float z);
	void rotateRad(const Vector3& xyz);
	void rotateDeg(float x, float y, float z);
	void rotateDeg(const Vector3& xyz);

	void scale(float x, float y, float z);
	void scale(const Vector3& xyz);

	/*
	Translates position, scale and rotate to Matrix4
	*/
	const Matrix4& convertToMatrix() const;
};

class Transform2D
{
	mutable Matrix4 matrix;
	mutable bool matrix_need_update = true;

	Vector2 position;
	Vector2 scope;
	float rotation;
public:
	Transform2D();
	virtual ~Transform2D() = default;

	void setPosition(float x, float y);
	void setPosition(const Vector2& xy);
	void move(float x, float y);
	void move(const Vector2& xy);
	const Vector2& getPosition() const;

	void setRotationRad(float radian);
	void setRotationDeg(float degrees);
	void rotateRad(float radian);
	void rotateDeg(float degrees);
	void rotateRad(float radian, const Vector2& center);
	void rotateDeg(float degrees, const Vector2& center);
	// changes only the position relatively the center
	void rotateRadOP(float radian, const Vector2& center);
	// changes only the position relatively the center
	void rotateDegOP(float degrees, const Vector2& center);
	float getRotation() const;

	void setScale(float x, float y);
	void setScale(const Vector2& xy);
	void scale(float x, float y);
	void scale(const Vector2& xy);
	void scale(const Vector2& xy, const Vector2& venter);
	// changes only the position relatively the center
	void scaleOP(const Vector2& xy, const Vector2& venter);
	const Vector2& getScale() const;

	/*
	* Translates position, scale and rotate to Matrix4
	*/
	const Matrix4& convertToMatrix() const;
};


}
}