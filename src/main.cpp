#include <iostream>
#include <windows.h>

#include "header.hpp"
#include "Graphics/AppInit.hpp"
#include "Window/Window.hpp"
#include "tests_with_ogl.hpp"
#include "Graphics/Shader.hpp"
#include "System/exception.hpp"
#include "Graphics/Vector.hpp"
#include <Graphics/Transformable.hpp>
#include <ctime>
#include "Graphics/TestObject.hpp"
#include "System/Clock.hpp"
#include "System/FpsMenager.hpp"
#include "Graphics/Image/Image.hpp"
#include "Graphics/Image/Texture.hpp"

std::ostream& operator<<(std::ostream&, const glm::mat3&);
std::ostream& operator<<(std::ostream&, const glm::mat4&);
std::ostream& operator<<(std::ostream&, const glm::vec2&);

using namespace hlvl::transform;
using namespace hlvl::vector;
using namespace hlvl::window;
using namespace hlvl::shader;
using namespace hlvl::camera;
using namespace hlvl::clock;
using namespace hlvl::fps_menager;
using namespace hlvl::image;
using namespace my;
using namespace hlvl::texture;

std::ostream& operator<<(std::ostream& stream, const Transform& t)
{
	stream << "[" << t.position.x << ", " << t.position.y << "], "
		<< "[" << t.scale.x << ", " << t.scale.y << "], "
		<< t.rotation;

	return stream;
}

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
	Uniform uni_matrix;
	Uniform uni_texture;
	try
	{
		std::string s1, s2, s3;
		compiler.loadFromFile("shader/texture.vert", Shader::Vertex, &s1);
		compiler.loadFromFile("shader/texture.frag", Shader::Fragment, &s2);
		shader = compiler.link(&s3);
		uni_matrix = shader.getLocation("transform");
		uni_texture = shader.getLocation("img");

		std::cout << s1 << ' ' << s2 << ' ' << s3 << std::endl;
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

	Camera camera;
	my::TestObject testObject;
	testObject.setVertexBuffer({
		{-0.5f, -0.7f},
		{0.5f, 0.7f},
		{0.5f, -0.7f},
		{-0.5f, -0.7f},
		{0.5f, 0.7f},
		{-0.5f, 0.7f}
	});
	testObject.v_buffer.updateData();
	/*
	testObject.setColorBuffer({
		{1.f, 1.f, 0.f},
		{1.f, 1.f, 1.f},
		{0.2f, 1.f, 1.f},
		{1.f, 1.f, 0.f},
		{1.f, 1.f, 1.f},
		{1.f, 1.f, 0.f},
	});/**/
	testObject.setColorBuffer({
		{1.f, 0.f, 1.f},
		{1.f, 0.f, 1.f},
		{1.f, 0.f, 1.f},
		{1.f, 0.f, 1.f},
		{1.f, 0.f, 1.f},
		{1.f, 0.f, 1.f},
		});
	testObject.c_buffer.updateData();
	testObject.setCoordsBuffer({
		{0.f, 1.f},
		{1.f, 0.f},
		{1.f, 1.f},
		{0.f, 1.f},
		{1.f, 0.f},
		{0.f, 0.f}
	});
	testObject.cord_buffer.updateData();

	Color3f fill_color(0.2f, 0.0f, 0.3f);

	FpsMenager fps_menager;
	fps_menager.setFps(60);

	Image img;
	try
	{
		img.loadFromFile("images/image.jpg");
	}
	catch (hlvl::image_error& e)
	{
		std::cerr << e.message << std::endl;
	}
	//PRINT(img.getSize());
	//PRINT(img.getPixel({350, 500}));
	Texture texture;
	texture.setImage(img);

	float delta = 0.f;

	bool window_will_close = false;
	while (window.isOpen())
	{
		delta = fps_menager.getDelta();
		fps_menager.beginOfRendering();

		if (window.shouldClose())
			window_will_close = true;

		window.clear(fill_color);

		if (GetAsyncKeyState('D'))
		{
			testObject.move(0.50f * delta, 0.f);
		}
		if (GetAsyncKeyState('A'))
		{
			testObject.move(-0.50f * delta, 0.f);
		}
		Matrix4 mvp;
		mvp = camera.getMatrix() * testObject.getMatrix();
		//PRINTR(delta);

		texture.activate();


		Shader::use(&shader);
		shader.setUniform(uni_matrix, mvp);
		shader.setUniform(uni_texture, texture);

		testObject.v_buffer.activate();
		testObject.c_buffer.activate();
		testObject.cord_buffer.activate();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		testObject.cord_buffer.deactivate();
		testObject.c_buffer.deactivate();
		testObject.v_buffer.deactivate();

		window.display();		

		if (window_will_close)
			window.close();

		fps_menager.endOfRendering();
	}

	return 0;
}