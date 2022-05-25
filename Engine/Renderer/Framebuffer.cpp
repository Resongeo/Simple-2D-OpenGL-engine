#include "Framebuffer.h"

namespace Cobalt
{
	Framebuffer::Framebuffer(int width, int height) : m_width(width), m_height(height) { CB_LOG_TRACE("{} {}", width, height); }

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &this->m_fbo);
		glDeleteTextures(1, &this->m_textureColorbuffer);
	}

	void Framebuffer::Create()
	{
		if (this->m_fbo)
		{
			glDeleteFramebuffers(1, &this->m_fbo);
			glDeleteTextures(1, &this->m_textureColorbuffer);
		}

		glGenFramebuffers(1, &this->m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_fbo);

		glGenTextures(1, &this->m_textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, this->m_textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_INT, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_textureColorbuffer, 0);

		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->m_width, this->m_height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			CB_LOG_ERROR("Framebuffer is incomplete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Resize(int width, int height)
	{
		this->m_width = width;
		this->m_height = height;
		Create();
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_fbo);
		glViewport(0, 0, this->m_width, this->m_height);
	}

	void Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}