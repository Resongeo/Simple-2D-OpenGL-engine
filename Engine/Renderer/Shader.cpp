#include "Shader.h"

Shader::Shader(const char* vertPath, const char* fragPath)
{
	/* Read shaders from files */
	std::string vertCode;
	std::string fragCode;
	std::ifstream vertShaderFile;
	std::ifstream fragShaderFile;

	vertShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::fstream::failbit | std::ifstream::badbit);

	try
	{
		vertShaderFile.open(vertPath);
		fragShaderFile.open(fragPath);
		std::stringstream vertShaderStream, fragShaderStream;

		vertShaderStream << vertShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();

		vertShaderFile.close();
		fragShaderFile.close();

		vertCode = vertShaderStream.str();
		fragCode = fragShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("ERROR! Failed to read shader file: %s, %s\n", vertPath, fragPath);
	}

	const char* vertShaderCode = vertCode.c_str();
	const char* fragShaderCode = fragCode.c_str();

	/* Compile shaders */
	unsigned int vertex, fragment;
	int succes;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertShaderCode, NULL);
	glCompileShader(vertex);
	/* Print errors */
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		printf("ERROR! Failed to compile vertex shader: %s\n", infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragShaderCode, NULL);
	glCompileShader(fragment);
	/* Print errors */
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		printf("ERROR! Failed to compile fragment shader: %s\n", infoLog);
	}

	/* Shader program */
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	/* Print errors */
	glGetProgramiv(ID, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		printf("ERROR! Failed to link shader program: %s\n", infoLog);
	}

	/* Delete shaders */
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::SetInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetVec2(const char* name, float xy) const
{
	glUniform2f(glGetUniformLocation(ID, name), xy, xy);
}

void Shader::SetVec2(const char* name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name), x, y);
}

void Shader::SetVec2(const char* name, glm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void Shader::SetVec3(const char* name, float xyz) const
{
	glUniform3f(glGetUniformLocation(ID, name), xyz, xyz, xyz);
}

void Shader::SetVec3(const char* name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::SetVec3(const char* name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void Shader::SetVec4(const char* name, float xyzw) const
{
	glUniform4f(glGetUniformLocation(ID, name), xyzw, xyzw, xyzw, xyzw);
}

void Shader::SetVec4(const char* name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void Shader::SetVec4(const char* name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.y, value.w);
}

void Shader::SetMat2(const char* name, glm::mat2 value) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const char* name, glm::mat3 value) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const char* name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
}
