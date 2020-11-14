#version 330

layout(location = 0) in vec2 Position;
layout(location = 1) in vec3 VertexColor;

out vec3 FragmentColor;

void main()
{
	gl_Position = vec4(Position.x, Position.y, 0.0, 1.0);

	FragmentColor = VertexColor;
}