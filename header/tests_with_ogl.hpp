#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include <vector>
#include <cmath>
#include "Graphics/Buffer.hpp"
#include "Graphics/Vector.hpp"

using namespace hlvl::vector;
using namespace hlvl::buffer;

namespace test1
{
	const static GLfloat vertexes[] = {
		0.f, 1.f, 0.f,
		1.f, -1.f, 0.f,
		-1.f, -1.f, 0.f
	};
	GLuint vertex_buffer;

	void create()
	{
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);
	}
	void draw()
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}
	void destroy()
	{
		glDeleteBuffers(1, &vertex_buffer);
	}
}
namespace test2
{
	const static GLfloat vertexes[] = {
		0.f, 0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		-0.5f, -0.5f, 0.f
	};
	const static GLfloat colors[] = {
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f
	};
	GLuint vertex_buf, color_buf;
	void create()
	{
		glGenBuffers(1, &vertex_buf);
		glGenBuffers(1, &color_buf);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, vertexes, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, color_buf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, colors, GL_STATIC_DRAW);
	}
	void draw()
	{
		// attribute 0: vertex
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		// attribute 1: color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, color_buf);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	void destroy()
	{
		glDeleteBuffers(1, &vertex_buf);
		glDeleteBuffers(1, &color_buf);
	}
}
namespace test2d
{
	/*
	const static GLfloat vertexes[] = {
		-0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f,
		-0.5f, -0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f
	};/**/
	const static GLfloat vertexes[] = {
		-1.f, -1.f,
		1.f, 1.f,
		-1.f, 1.f,
		-1.f, -1.f,
		1.f, 1.f,
		1.f, -1.f
	};
	/*
	const static GLfloat colors[] = {
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f,
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f
	};/**/
	const static GLfloat colors[] = {
		1.f, 0.5f, 0.f,
		0.f, 1.f, 0.5f,
		0.5f, 0.f, 1.f,
		1.f, 0.5f, 0.f,
		0.f, 1.f, 0.5f,
		0.5f, 0.f, 1.f
	};
	GLuint vertex_buf, color_buf;
	void create()
	{
		glGenBuffers(1, &vertex_buf);
		glGenBuffers(1, &color_buf);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, color_buf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	}
	void draw()
	{
		// attribute 0: vertex
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		// attribute 1: color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, color_buf);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	void destroy()
	{
		glDeleteBuffers(1, &vertex_buf);
		glDeleteBuffers(1, &color_buf);
	}
}

namespace
{
	float rad(float angle)
	{
		return angle * 3.1415926535f / 180.f;
	}
	glm::vec2 getCirclePoint(float rad)
	{
		glm::vec2 output;
		output.x = cos(rad);
		output.y = sin(rad);
		return output;
	}
}
namespace neon
{
	std::vector<Point2D> vertexes;
	std::vector<Color4f> colors;
	Color3f color;

	GLuint vertex_buf, color_buf;

	constexpr size_t TRIANGLE_COUNT = 5;
	const size_t VERTEX_COUNT = TRIANGLE_COUNT * 3;

	void create()
	{		
		// calculate positions and colors
		const float ANGLE = 360.f / (float)TRIANGLE_COUNT;
		float angle = 0.f;

		color = Color3f(0.8f, 0.5f, 0.1f);

		vertexes.resize(VERTEX_COUNT);
		colors.resize(VERTEX_COUNT);
		for (size_t i = 0; i < VERTEX_COUNT; i += 3)
		{
			// one sector
			vertexes[i] = Point2D();
			vertexes[i + 1] = getCirclePoint(rad(angle));
			angle += ANGLE;
			vertexes[i + 2] = getCirclePoint(rad(angle));

			// only center is not transparent
			colors[i] = Color4f(color, 1.f);
			colors[i + 1] = Color4f(color, 0.f);
			colors[i + 2] = Color4f(color, 0.f);
		}

		// bind to opengl
		glGenBuffers(1, &vertex_buf);
		glGenBuffers(1, &color_buf);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertexes.size(), vertexes.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, color_buf);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * colors.size(), colors.data(), GL_STATIC_DRAW);
	}
	void draw()
	{
		// attribute 0 : position
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		// attribute 1 : color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, color_buf);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0, VERTEX_COUNT);

		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	void destroy()
	{
		glDeleteBuffers(1, &vertex_buf);
		glDeleteBuffers(1, &color_buf);
	}
}

namespace indexing
{
	VertexBuffer2D* vert;
	ColorBuffer3f* color;

	void create()
	{
		vert = new VertexBuffer2D;
		color = new ColorBuffer3f;

		vert->add({
			{-0.5f, -0.5f},
			{0.5f, -0.5f},
			{0.5f, 0.5f},
			{-0.5f, 0.5f} });
		color->add({
			{0.5f, 0.5f, 1.f} });
	}
	void draw()
	{

	}
	void destroy()
	{
		delete vert;
		delete color;
	}
}