#include "Renderer.h"

namespace Cobalt
{
	Renderer::Renderer(Shader& defaultShader, Sprite& defaultSprite) : m_defaultShader(defaultShader), m_defaultSprite(defaultSprite), m_shader(defaultShader), m_sprite(defaultSprite) { }

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

	void Renderer::SetShader(Shader& shader)
	{
		this->m_shader = shader;
	}

	void Renderer::SetSprite(Sprite& sprite)
	{
		this->m_sprite = sprite;
	}

	void Renderer::DrawQuad(glm::mat4 transform, glm::mat4 projection, Sprite& sprite, glm::vec3 color)
	{
		this->m_shader.Use();

		this->m_shader.SetMat4("projection", projection);
		this->m_shader.SetMat4("view", glm::mat4(1.0));
		this->m_shader.SetMat4("transform", transform);
		this->m_shader.SetVec4("color", glm::vec4(color, 1.0f));

		glActiveTexture(GL_TEXTURE0);
		sprite.Bind();

		glBindVertexArray(this->m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::DrawQuad(glm::mat4 transform, glm::mat4 projection, Sprite& sprite)
	{
		this->m_shader.Use();

		this->m_shader.SetMat4("projection", projection);
		this->m_shader.SetMat4("view", glm::mat4(1.0));
		this->m_shader.SetMat4("transform", transform);
		this->m_shader.SetVec4("color", glm::vec4(1.0f));

		glActiveTexture(GL_TEXTURE0);
		sprite.Bind();

		glBindVertexArray(this->m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::DrawQuad(glm::mat4 transform, glm::mat4 projection, glm::vec3 color)
	{
		this->m_shader.Use();

		this->m_shader.SetMat4("projection", projection);
		this->m_shader.SetMat4("view", glm::mat4(1.0));
		this->m_shader.SetMat4("transform", transform);
		this->m_shader.SetVec4("color", glm::vec4(color, 1.0f));

		glActiveTexture(GL_TEXTURE0);
		this->m_defaultSprite.Bind();

		glBindVertexArray(this->m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Renderer::DrawQuad(glm::mat4 transform, glm::mat4 projection)
	{
		this->m_defaultShader.Use();

		this->m_defaultShader.SetMat4("projection", projection);
		this->m_defaultShader.SetMat4("view", glm::mat4(1.0));
		this->m_defaultShader.SetMat4("transform", transform);
		this->m_defaultShader.SetVec4("color", glm::vec4(1.0f));

		glActiveTexture(GL_TEXTURE0);
		this->m_defaultSprite.Bind();

		glBindVertexArray(this->m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}