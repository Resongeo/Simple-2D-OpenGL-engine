#include "ImGui_CobaltEngine_Impl.h"
#include "Core/Cobalt.h"
#include "Core/Window.h"
#include "Renderer/Shader.h"

float deltaTime;
float lastFrame;

float fpsRefreshInterval = 0.5f;
float nextTimeToRefreshFPS = 1.0f;
float fpsCounter = 0.0f;

int main()
{
	Cobalt::Log::Init();
	Cobalt::Window window(1920, 1080, "Cobalt Engine");
	window.SetVsync(false);

	Cobalt::Shader defaultShader("resources/shaders/Default.vert", "resources/shaders/Default.frag");

	/* Temporary code */
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Cobalt::ImGUI::Init(window.GetWindow());
	Cobalt::ImGUI::SetupStyle();

	float bg_col[3] = { 0.15, 0.16, 0.17 };
	float rect_col[3] = { 0.24, 0.47, 0.65 };
	float edge_smoothness = 0.005;

	bool showDemoWindow = false;

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		/* Delta Time */
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (fpsRefreshInterval < 0.0f) {
			fpsCounter = 1.0f / deltaTime;
			fpsRefreshInterval = nextTimeToRefreshFPS;
		}
		else {
			fpsRefreshInterval -= deltaTime;
		}

		glClearColor(bg_col[0], bg_col[1], bg_col[2], 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwPollEvents();
		Cobalt::ImGUI::NewFrame();

		{
			ImGui::Begin("Test window");

			ImGui::Text("");
			ImGui::ColorEdit3("Background", bg_col);
			ImGui::Spacing();
			ImGui::ColorEdit3("Circle color", rect_col);
			ImGui::Spacing(); ImGui::Spacing();
			ImGui::SliderFloat("Falloff", &edge_smoothness, 0.005f, 0.1f, "%.3f");

			ImGui::Text("");
			ImGui::Checkbox("Show demo window", &showDemoWindow);

			ImGui::End();
		}
		{
			bool open = true;
			ImGui::Begin("FPS", &open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

			ImGui::Text(("FPS: " + std::to_string((int)fpsCounter)).c_str());

			ImGui::End();
		}

		if (showDemoWindow) ImGui::ShowDemoWindow();

		defaultShader.Use();
		defaultShader.SetVec3("custom_color", rect_col[0], rect_col[1], rect_col[2]);
		defaultShader.SetVec3("bg_col", bg_col[0], bg_col[1], bg_col[2]);
		defaultShader.SetVec2("resulotion", glm::vec2(window.GetWidth(), window.GetHeight()));
		defaultShader.SetFloat("edge_smoothness", edge_smoothness);
		defaultShader.SetFloat("iTime", glfwGetTime());
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		Cobalt::ImGUI::Render();
		glfwSwapBuffers(window.GetWindow());
	}

	Cobalt::ImGUI::ShutDown();
	window.Destroy();

	return 0;
}