#pragma once

#include "Cobalt.h"

namespace Cobalt
{
	class Window
	{
	public:
		Window(int width, int height, const char* title);

		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }
		const char* GetTitle() { return m_title; }
		GLFWwindow* GetWindow() { return m_window; }

		void SetVsync(bool value);
		void Destroy();

	private:
		int m_width;
		int m_height;
		const char* m_title;

		GLFWwindow* m_window;
	};
}