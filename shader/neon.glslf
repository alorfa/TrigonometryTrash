#version 330

in vec4 fragment_color;

out vec3 color;

uniform vec3 back_color;

void main()
{
	color = fragment_color.xyz * fragment_color.w + back_color * (1.0 - fragment_color.w);
}