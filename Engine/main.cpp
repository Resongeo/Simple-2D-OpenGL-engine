#include "Core/Cobalt.h"
#include "Core/Window.h"

int main()
{
	Cobalt::Log::Init();
	Cobalt::Window window(1280, 720, "Cobalt Engine");
	window.SetVsync(true);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window.GetWindow());
	}

	window.Destroy();

	return 0;
}