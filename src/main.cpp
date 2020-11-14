#include <iostream>
#include <windows.h>

#include "header.hpp"
#include "Graphics/AppInit.hpp"
#include "Window/Window.hpp"
#include "tests_with_ogl.hpp"
#include "Graphics/Shader.hpp"
#include "System/exception.hpp"
#include "Graphics/Vector.hpp"
#include <Graphics/Transform.hpp>
#include <ctime>

std::ostream& operator<<(std::ostream&, const glm::mat3&);
std::ostream& operator<<(std::ostream&, const glm::mat4&);
std::ostream& operator<<(std::ostream&, const glm::vec2&);

using namespace hlvl::transform;
using namespace hlvl::vector;
using namespace hlvl::window;
using namespace hlvl::shader;

int main()
{
	hlvl::GLFW just_glfw;
	Window window;

	if (!just_glfw.init())
	{
		std::cerr << "GLFW cannot be initialized" << std::endl;
		exit(1);
	}

	if (!window.create(800, 800, "title"))
	{
		std::cerr << "Window cannot be created" << std::endl;
		exit(1);
	}

	//open shaders
	ShaderCompiler compiler;
	Shader shader;
	Uniform uniform;
	try
	{
		compiler.loadFromFile("shader/neon.glslv", Shader::Vertex, nullptr);
		compiler.loadFromFile("shader/neon.glslf", Shader::Fragment, nullptr);
		shader = compiler.link(nullptr);
		uniform = shader.getLocation("back_color");
	}
	catch (hlvl::file_not_found& e)
	{
		std::cerr << "File " << e.filename << " not found" << std::endl;
		exit(1);
	}
	catch (hlvl::shader_error& e)
	{
		std::cerr << "Shader error: " << e.message << std::endl;
		exit(1);
	}

	/*
	Transform2D test;
	test.position.x = 5.f;
	test.scale(2.f, 2.f);
	Matrix4 matrix;
	test.convertToMatrix(matrix);
	std::cout << matrix << std::endl;
	Point2D point(10.f, 20.f);
	PRINT(matrix * glm::vec4(point, 0.f, 1.f));*/

	Transform2D test;
	double begin = clock();
	for (size_t i = 0; i < 10000; i++)
	{
		test.move(0.1f, 0.f);
		test.convertToMatrix();
	}
	PRINT(clock() - begin);

	indexing::create();

	Color3f fill_color(0.2f, 0.0f, 0.3f);

	bool window_will_close = false;
	while (window.isOpen())
	{
		if (window.shouldClose())
			window_will_close = true;

		window.clear(fill_color);

		Shader::use(&shader);
		shader.setUniform(uniform, fill_color);
		indexing::draw();

		window.display();		

		Sleep(10);

		if (window_will_close)
			window.close();				
	}

	indexing::destroy();

	return 0;
}