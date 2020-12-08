#version 330

in vec3 fragment_color;
in vec2 frag_UV;

uniform sampler2D img;
uniform sampler2D img2;

out vec4 color;

void main()
{
	//vec3 tex_color = texture(img, frag_UV).rgb;
	//tex_color.r = tex_color.g = tex_color.b = (tex_color.r + tex_color.g + tex_color.b) / 3;

	color = texture(img, frag_UV);

		//(abs(cos((frag_UV.x - 0.5) * 3.1415926535) / 2) + 0.5);
		//(abs(cos((frag_UV.y - 0.5) * 3.1415926535) / 2) + 0.5);
	
}