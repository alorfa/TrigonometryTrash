#version 330

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec4 in_vertex_color;

out vec4 fragment_color;

void main()
{
	gl_Position.xyz = vec3(in_position, 1.0);
	fragment_color = in_vertex_color;
}