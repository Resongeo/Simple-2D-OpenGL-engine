#pragma once

#include "glad/glad.h"
#include "Utils/Math.h"
#include "Renderer/Shader.h"
#include "Renderer/Sprite.h"

namespace Cobalt
{
	class Renderer
	{
	public:
		Renderer(Shader& defaultShader, Sprite& defaultSprite);
		~Renderer();

		void Init();

		void SetShader(Shader& shader);
		void SetSprite(Sprite& sprite);

		void DrawQuad(glm::mat4 transform, glm::mat4 projection, Sprite& sprite, glm::vec3 color);
		void DrawQuad(glm::mat4 transform, glm::mat4 projection, Sprite& sprite);
		void DrawQuad(glm::mat4 transform, glm::mat4 projection, glm::vec3 color);
		void DrawQuad(glm::mat4 transform, glm::mat4 projection);

	private:
		Shader m_shader;
		Shader m_defaultShader;
		Sprite m_sprite;
		Sprite m_defaultSprite;
		unsigned int m_vao;
	};
}