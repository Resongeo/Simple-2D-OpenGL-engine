#include "Window.h"

namespace Cobalt
{
	Window::Window(int width, int height, const char* title)
	{
		m_title = title;

		if (!glfwInit()) CB_LOG_ERROR("Failed to initialize GLFW!");
		else CB_LOG_INFO("GLFW initialized.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!m_window) CB_LOG_ERROR("Failed to create window!");
		else CB_LOG_INFO("Window created. Dimensions: {}x{} title:{}", width, height, title);
		m_monitor = glfwGetPrimaryMonitor();

		glfwMakeContextCurrent(m_window);

		glfwSetFramebufferSizeCallback(m_window, Window::FrameBuffer_Size_Callback);
		glfwSetErrorCallback(Window::Error_Callback);

		int sys_width = GetSystemMetrics(SM_CXSCREEN);
		int sys_height = GetSystemMetrics(SM_CYSCREEN);
		glfwSetWindowMonitor(m_window, nullptr, (sys_width / 2) - (width / 2), (sys_height / 2) - (height / 2), width, height, GLFW_DONT_CARE);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) CB_LOG_ERROR("Failed to load GLAD!");
		else
			printf("OpenGL version: %s\n", glGetString(GL_VERSION));
			printf("Renderer device: %s\n", glGetString(GL_RENDERER));
	}

	float Window::GetWidth()
	{
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		return static_cast<float>(width);
	}

	float Window::GetHeight()
	{
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		return static_cast<float>(height);
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

	void Window::Error_Callback(int, const char* error_message)
	{
		CB_LOG_ERROR("GFLW error: {}", error_message);
	}
}