#pragma once

#include "Graphics/Camera.hpp"

namespace hlvl
{

namespace window
{
	class Window;
}

namespace drawable
{

	class Drawable
	{
		virtual void draw(const camera::CameraBase& camera) const = 0;

		friend class window::Window;
	};

}
}