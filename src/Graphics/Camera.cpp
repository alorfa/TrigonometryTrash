#include <Graphics/Camera.hpp>

using namespace hlvl::transform;
using namespace hlvl::matrix;

namespace hlvl
{
namespace camera
{


	CameraBase::CameraBase(const Transform& other)
		: Transformable(other) {}

	Camera::Camera() {}

	Camera::Camera(const Transform& other)
		: CameraBase(other) {}

	Camera::Camera(const Camera& other)
		: CameraBase(other.getTransform()) {}

	Camera& Camera::operator=(const Transform& other)
	{
		setTransform(other);
		return *this;
	}
	Camera& Camera::operator=(const Camera& other)
	{
		setTransform(other.getTransform());
		return *this;
	}
	Matrix4& Camera::getMatrix() const
	{
		if (matrix_need_update)
		{
			float cosine = cos(getRotation());
			float sine = sin(getRotation());
			float scalxc = 1.f / getScale().x * cosine;
			float scalyc = 1.f / getScale().y * cosine;
			float scalxs = 1.f / getScale().x * sine;
			float scalys = 1.f / getScale().y * sine;
			float tx = getPosition().x;
			float ty = getPosition().y;

			matrix = glm::mat4(
				{scalxc,	scalxs,	0.f,	0.f},
				{-scalys,	scalyc,	0.f,	0.f},
				{0.f,		0.f,	1.f,	0.f},
				{-tx,		-ty,	0.f,	1.f});
		}
		matrix_need_update = false;

		return matrix;
	}
	const Camera Camera::default_camera{};

}
}