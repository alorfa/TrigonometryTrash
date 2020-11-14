#include "Window/Window.hpp"
#include "Graphics/AppInit.hpp"

namespace hlvl
{
namespace window
{


Window::Window()
	: window(nullptr), camera(nullptr) {}

bool Window::create(GLuint width, GLuint height, const char* title)
{
	// destroy the previous window 
	close();

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (window)
	{
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			return false; //return false if GLEW has no initialized
		return true;
	}
	return false; //and if window has no created
}
Window::Window(GLuint width, GLuint height, const char* title)
	: camera(nullptr)
{
	this->create(width, height, title);
}
void Window::close()
{
	if (window)
		glfwDestroyWindow(window);
	window = nullptr;
}
Window::~Window()
{
	close();
}

bool Window::isOpen()
{
	return (bool)window;
}
bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::setCamera(CameraBase* new_camera)
{
	camera = new_camera;
}
void Window::clear(const Color3b& fill)
{
	glClearColor(
		(float)fill.r / 255.f,
		(float)fill.g / 255.f,
		(float)fill.b / 255.f,
		1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::clear(const Color3f& color)
{
	glClearColor(color.r, color.g, color.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::display()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}


}
}