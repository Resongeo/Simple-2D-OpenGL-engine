#pragma once

#include "Cobalt.h"

namespace Cobalt
{
	class Window
	{
	public:
		Window(int width, int height, const char* title);

		int GetWidth();
		int GetHeight();
		const char* GetTitle() { return m_title; }
		GLFWwindow* GetWindow() { return m_window; }
		GLFWmonitor* GetMonitor() { return m_monitor; }

		void SetVsync(bool value);
		void Destroy();

	private:
		const char* m_title;
		GLFWwindow* m_window;
		GLFWmonitor* m_monitor;

		/* Callback methods */

		static void FrameBuffer_Size_Callback(GLFWwindow* window, int width, int height);
	};
}