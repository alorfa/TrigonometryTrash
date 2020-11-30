#version 330

layout(location = 0) in vec2 input_pos;
layout(location = 1) in vec3 input_color;
layout(location = 2) in vec2 input_UV;

out vec3 fragment_color;
out vec2 frag_UV;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(input_pos, 0, 1);
	fragment_color = input_color;
	frag_UV = input_UV;
}