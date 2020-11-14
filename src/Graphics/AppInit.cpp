#include "Graphics/AppInit.hpp"

#include <GL/glew.h>
#include <GL/GL.h>
#include <GLFW/glfw3.h>

namespace hlvl
{
	GLFW::GLFW() {}
	bool GLFW::init()
	{
		return glfwInit();
	}
	GLFW::~GLFW()
	{
		glfwTerminate();
	}
}