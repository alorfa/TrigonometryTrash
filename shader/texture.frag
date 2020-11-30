#version 330

in vec3 fragment_color;
in vec2 frag_UV;

uniform sampler2D img;

out vec4 color;

void main()
{
	vec3 tex_color = texture(img, frag_UV).rgb;
	tex_color.r = tex_color.g = tex_color.b = (tex_color.r + tex_color.g + tex_color.b) / 3;
	color = vec4(tex_color, 1);
	
}