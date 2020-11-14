#include <Graphics/Camera.hpp>

namespace hlvl
{
namespace camera
{


const Matrix4& Camera3D::getMatrix() const
{
	return transform.convertToMatrix();
}

Camera2D::Camera2D()
	: transform() {}

Camera2D::Camera2D(const Transform2D& other)
	: transform(other) {}

Camera2D::Camera2D(const Camera2D& other)
	: transform(other.transform) {}

Camera2D& Camera2D::operator=(const Transform2D& other)
{
	transform = other;
	return *this;
}
Camera2D& Camera2D::operator=(const Camera2D& other)
{
	transform = other.transform;
	return *this;
}
const Matrix4& Camera2D::getMatrix() const
{
	return transform.convertToMatrix();
}

}
}