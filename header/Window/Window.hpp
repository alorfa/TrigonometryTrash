#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>

#include "header.hpp"

#include "Graphics/Vector.hpp"
#include <Graphics/Camera.hpp>

using namespace hlvl::camera;

namespace hlvl
{
namespace window
{


class Window
{
	GLFWwindow* window;

	CameraBase* camera;
public:
	Window();
	bool create(GLuint width, GLuint height, const char* title);
	Window(GLuint width, GLuint height, const char* title);
	void close();
	~Window();

	bool isOpen();

	bool shouldClose();

	void setCamera(CameraBase* new_camera);

	void clear(const Color3b& fill);
	void clear(const Color3f& fill);
	void display();
};


}
}