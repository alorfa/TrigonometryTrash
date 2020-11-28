#pragma once

#include <Graphics/Matrix.hpp>
#include <Graphics/Vector.hpp>
#include <memory>

namespace hlvl
{
namespace transform
{


	class Transform
	{
		using Matrix4 = matrix::Matrix4;
		using Vector2 = vector::Vector2;
	public:	
		Vector2 position;
		Vector2 scale;
		float rotation;

		Transform();
		Transform(const Transform&) = default;
		Transform(const Vector2& position, const Vector2& scale, float rotation);

		Transform& operator=(const Transform&) = default;

		void setTransform(const Transform&);
	};

	class Transformable
	{
		using Matrix4 = matrix::Matrix4;
		using Vector2 = vector::Vector2;
	protected:
		Transform transform;

		mutable Matrix4 matrix;
		mutable bool matrix_need_update = true;
	public:
		Transformable();
		Transformable(const Vector2& position, const Vector2& scale, float rotation);
		Transformable(const Transform&);
		virtual ~Transformable() = default;

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
		void scale(const Vector2& xy, const Vector2& center);
		// changes only the position relatively the center
		void scaleOP(const Vector2& xy, const Vector2& center);
		const Vector2& getScale() const;

		void setTransform(const Transform& other);
		const Transform& getTransform() const;

		Transformable& operator=(const Transformable&) = delete;
		/*
		* Translates position, scale and rotate to Matrix4
		*/
		virtual Matrix4& getMatrix() const;
	};


}
}