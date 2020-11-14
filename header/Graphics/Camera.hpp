#pragma once

#include <Graphics/Transform.hpp>

using namespace hlvl::transform;

namespace hlvl
{
namespace camera
{


class CameraBase
{
public:
	CameraBase() = default;

	virtual const Matrix4& getMatrix() const = 0;
};
class Camera3D : public CameraBase
{
public:
	Transform3D transform;

	const Matrix4& getMatrix() const override;
};
class Camera2D : public CameraBase
{
public:
	Transform2D transform;

	Camera2D();
	Camera2D(const Transform2D& transform);
	Camera2D(const Camera2D& other);
	Camera2D& operator=(const Transform2D& other);
	Camera2D& operator=(const Camera2D& other);

	const Matrix4& getMatrix() const override;
};


}
}