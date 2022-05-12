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
		Renderer(Shader& defaultShader);
		~Renderer();

		void Init();

		void DrawQuad(glm::mat4 transform, glm::mat4 projection, Sprite& sprite, glm::vec3 color);

	private:
		Shader shader;
		unsigned int m_vao;
	};
}