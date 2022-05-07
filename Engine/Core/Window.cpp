#include "Window.h"

namespace Cobalt
{
	Window::Window(int width, int height, const char* title)
	{
		m_width = width;
		m_height = height;
		m_title = title;

		if (!glfwInit()) CB_LOG_ERROR("Failed to initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(1280, 720, "Cobalt Engine", nullptr, nullptr);
		if (!m_window) CB_LOG_ERROR("Failed to create window!");

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) CB_LOG_ERROR("Failed to load GLAD!");
	}

	void Window::SetVsync(bool value) { glfwSwapInterval((int)value); }

	void Window::Destroy()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}