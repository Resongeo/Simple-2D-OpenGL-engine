#include "Window.h"

namespace Cobalt
{
	Window::Window(int width, int height, const char* title)
	{
		m_title = title;

		if (!glfwInit()) CB_LOG_ERROR("Failed to initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!m_window) CB_LOG_ERROR("Failed to create window!");
		m_monitor = glfwGetPrimaryMonitor();

		glfwMakeContextCurrent(m_window);

		glfwSetFramebufferSizeCallback(m_window, Window::FrameBuffer_Size_Callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) CB_LOG_ERROR("Failed to load GLAD!");
	}

	int Window::GetWidth()
	{
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		return width;
	}

	int Window::GetHeight()
	{
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		return height;
	}

	void Window::SetVsync(bool value) { glfwSwapInterval((int)value); }

	void Window::Destroy()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	/* Callback methods */

	void Window::FrameBuffer_Size_Callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}