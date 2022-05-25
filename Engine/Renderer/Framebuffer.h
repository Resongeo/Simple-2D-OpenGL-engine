#pragma once

#include "glad/glad.h"

#include "Utils/Log.h"

namespace Cobalt
{
	class Framebuffer
	{
	public:
		Framebuffer(int width, int height);
		~Framebuffer();

		void Create();
		void Resize(int width, int height);

		void Bind();
		void Unbind();

		unsigned int GetColorbuffer() const { return m_textureColorbuffer; }

	private:
		int m_width, m_height;
		unsigned int m_fbo = 0;
		unsigned int m_textureColorbuffer = 0;
	};
}