#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform vec3 custom_color;
uniform vec3 bg_col;
uniform vec2 resulotion;
uniform float edge_smoothness;

void main()
{
	vec2 uv = TexCoords;
	uv -= .5;
	uv.x *= resulotion.x / resulotion.y;

	float d = length(uv);
	float r = 0.3;
	float c = smoothstep(r, r - edge_smoothness, d);

	vec3 col = vec3(c);
	vec3 bg = vec3(1.0 - col.x, 1.0 - col.y, 1.0 - col.z);
	col *= custom_color;
	bg *= bg_col;
	col += bg;

	FragColor = vec4(col, 1.0);
}