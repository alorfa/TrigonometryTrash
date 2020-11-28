#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>

#include "header.hpp"

#include "Graphics/Vector.hpp"
#include <Graphics/Camera.hpp>

namespace hlvl
{
namespace window
{


	class Window
	{
		using CameraBase = camera::CameraBase;
		using Color3f = vector::Color3f;
		using Color3b = vector::Color3b;

		GLFWwindow* window;

		const CameraBase* camera;

		GLuint frame_limit;
	public:
		Window();
		bool create(GLuint width, GLuint height, const char* title);
		Window(GLuint width, GLuint height, const char* title);
		Window(const Window&) = delete;
		void close();
		~Window();

		bool isOpen();

		bool shouldClose();

		void setFrameLimit(GLuint limit);
		GLuint getFrameLimit();

		void setCamera(const CameraBase& new_camera);

		void clear(const Color3b& fill);
		void clear(const Color3f& fill);
		void display();
	};


}
}