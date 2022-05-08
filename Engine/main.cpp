#include "ImGui_CobaltEngine_Impl.h"
#include "Core/Cobalt.h"
#include "Core/Window.h"
#include "Renderer/Shader.h"


int main()
{
	Cobalt::Log::Init();
	Cobalt::Window window(1280, 720, "Cobalt Engine");
	window.SetVsync(true);

	Cobalt::Shader defaultShader("shaders/Default.vert", "shaders/Default.frag");

	/* Temporary code */
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Cobalt::ImGUI::Init(window.GetWindow());
	Cobalt::ImGUI::SetupStyle();

	float bg_col[3] = { 0.14, 0.14, 0.14 };

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		glClearColor(bg_col[0], bg_col[1], bg_col[2], 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwPollEvents();
		Cobalt::ImGUI::NewFrame();

		{
			ImGui::Begin("Test window");

			ImGui::ColorEdit3("Background", bg_col);

			ImGui::End();
		}

		defaultShader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		Cobalt::ImGUI::Render();
		glfwSwapBuffers(window.GetWindow());
	}

	Cobalt::ImGUI::ShutDown();
	window.Destroy();

	return 0;
}