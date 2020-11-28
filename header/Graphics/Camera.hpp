#pragma once

#include <Graphics/Transformable.hpp>


namespace hlvl
{
namespace camera
{


	class CameraBase : public transform::Transformable
	{
	protected:
		using Matrix4 = matrix::Matrix4;
		using Transformable = transform::Transformable;
		using Transform = transform::Transform;
	public:
		CameraBase() = default;
		CameraBase(const Transform&);
		virtual ~CameraBase() = default;


		Matrix4& getMatrix() const override = 0;
	};
	class Camera : public CameraBase
	{
	public:
		Camera();
		Camera(const Transform& transform);
		Camera(const Camera& other);
		Camera& operator=(const Transform& other);
		Camera& operator=(const Camera& other);

		Matrix4& getMatrix() const override;

		static const Camera default_camera;
	};


}
}