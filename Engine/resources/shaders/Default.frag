#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D sprite;
uniform vec4 color;

void main()
{
	FragColor = color * texture(sprite, TexCoords);
}