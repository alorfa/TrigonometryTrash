#version 330

in vec3 fragment_color;

out vec3 color;

void main()
{
	color = fragment_color;
}