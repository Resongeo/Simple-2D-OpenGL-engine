#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform vec2 iResulotion;
uniform float intensity;
uniform float size;

uniform vec3 color_1;
uniform vec3 color_2;

vec3 lerp(vec3 a, vec3 b, float t);
vec3 pow3(vec3 col, float value);

void main()
{
	vec2 uv = TexCoords;
	vec3 col1 = vec3(0.0);
	vec3 col2 = vec3(1.0);
	vec3 col = lerp(col1, col2, 1 - uv.y) * lerp(col1, col2, uv.y) * lerp(col1, col2, 1 - uv.x) * lerp(col1, col2, uv.x);
	col = pow3(col, size);

	vec3 inverted = pow3(col, 0.1);
	inverted = 1-inverted;
	inverted *= color_1;

	FragColor = vec4(inverted, 1.0);
}

vec3 lerp(vec3 a, vec3 b, float t)
{
	return (a + t * (b - a));
}

vec3 pow3(vec3 col, float value)
{
	return vec3(pow(col.x, value), pow(col.y, value), pow(col.z, value));
}