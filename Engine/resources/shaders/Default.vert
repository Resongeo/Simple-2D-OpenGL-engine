#version 330 core

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main()
{
	TexCoords = vertex.zw;
	gl_Position = projection * view * transform * vec4(vertex.xy, 0.0, 1.0);
}