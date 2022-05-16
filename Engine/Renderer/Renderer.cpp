#include "Renderer.h"

namespace Cobalt
{
	Renderer::Renderer(Shader& defaultShader) : shader(defaultShader) { }

	Renderer::~Renderer()
	{
		glDeleteVertexArrays(1, &this->m_vao);
	}

	void Renderer::Init()
	{
		float vertices[] = {
			 0.5f,  0.5f, 1.0f, 1.0f,
			 0.5f, -0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		unsigned int vbo, ebo;
		glGenVertexArrays(1, &this->m_vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glBindVertexArray(this->m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void Renderer::DrawQuad(glm::mat4 transform, glm::mat4 projection, Sprite& sprite, glm::vec3 color)
	{
		this->shader.Use();

		this->shader.SetMat4("projection", projection);
		this->shader.SetMat4("view", glm::mat4(1.0));
		this->shader.SetMat4("transform", transform);
		this->shader.SetVec4("color", glm::vec4(color, 1.0f));

		glActiveTexture(GL_TEXTURE0);
		sprite.Bind();

		glBindVertexArray(this->m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}