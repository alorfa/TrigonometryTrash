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
#include "TestClasses/TestObject.hpp"
#include "System/Clock.hpp"
#include "System/FpsMenager.hpp"
#include "Graphics/Image/Image.hpp"
#include "Graphics/Image/Texture.hpp"
#include "TestClasses/Sprite.hpp"

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
using namespace sprite;

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

	if (not just_glfw.init())
	{
		std::cerr << "GLFW cannot be initialized" << std::endl;
		exit(1);
	}
	
	/*
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/**/

	if (not window.create(800, 1000, "title"))
	{
		std::cerr << "Window cannot be created" << std::endl;
		exit(1);
	}

	//open shaders
	Shader shader;
	Uniform uni_matrix;
	Uniform uni_texture;
	Uniform uni_texture2;
	try
	{
		std::string s1, s2, s3;
		ShaderCompiler compiler;
		compiler.loadFromFile("shader/texture.vert", Shader::Vertex, &s1);
		compiler.loadFromFile("shader/texture.frag", Shader::Fragment, &s2);
		shader = compiler.link(&s3);
		uni_matrix = shader.getLocation("transform");
		uni_texture = shader.getLocation("img");
		uni_texture2 = shader.getLocation("img2");

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

	Color3f fill_color(0.0f, 0.0f, 0.0f);

	FpsMenager fps_menager;
	//fps_menager.setFps(60);

	Sprite sprite;
	Texture texture;
	try
	{
		Image img;
		img.loadFromFile("images/image.jpg");
		texture.setImage(img);
	}
	catch (hlvl::image_error& e)
	{
		std::cerr << e.message << std::endl;
		exit(1);
	}
	sprite.setTexture(texture);

	try
	{
		Shader::getShader(Shader::Inbuilt::TexturedVertexes);
	}
	catch (hlvl::shader_error& e)
	{
		std::cout << e.message << std::endl;
		exit(1);
	}

	float delta = 0.f;
	
	sprite.setScale(0.7f, 0.7f);

	bool window_will_close = false;
	while (window.isOpen())
	{
		delta = fps_menager.getDelta();
		//fps_menager.beginOfRendering();

		if (window.shouldClose())
			window_will_close = true;

		if (GetAsyncKeyState('W'))
			sprite.move(0.f, 1.50f * delta);
		if (GetAsyncKeyState('S'))
			sprite.move(0.f, -1.50f * delta);
		if (GetAsyncKeyState('D'))
			sprite.move(1.50f * delta, 0.f);
		if (GetAsyncKeyState('A'))
			sprite.move(-1.50f * delta, 0.f);
		if (GetAsyncKeyState(VK_UP))
			sprite.setTextureRect( { 0, 0 }, { 300, 300 } );
		if (GetAsyncKeyState(VK_DOWN))
			sprite.setTextureRect({ 0, 0 }, texture.getSize());

		window.clear(fill_color);
		window.draw(sprite);
		window.display();		

		if (window_will_close)
			window.close();

		//fps_menager.endOfRendering();
	}

	return 0;
}