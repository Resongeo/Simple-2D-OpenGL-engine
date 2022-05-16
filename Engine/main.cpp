#include "ImGui_CobaltEngine_Impl.h"
#include "Core/Cobalt.h"
#include "Core/Window.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

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
	Cobalt::Sprite sprite("resources/sprites/test.jpg");

	Cobalt::Renderer Renderer2D(defaultShader);
	Renderer2D.Init();


	Cobalt::ImGUI::Init(window.GetWindow());
	Cobalt::ImGUI::SetupStyle();

	float bg_col[3] = { 0.15, 0.16, 0.17 };
	float sprite_tint[3] = { 1.0, 1.0, 1.0 };

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

		#pragma region ImGui

		{
			ImGui::Begin("Test window");

			ImGui::Text("");
			ImGui::ColorEdit3("Background", bg_col);
			ImGui::Spacing();
			ImGui::ColorEdit3("Sprite tint", sprite_tint);
			ImGui::Spacing();

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

		#pragma endregion


		float camera_size = 4.f;
		float left = -((window.GetWidth() / window.GetHeight()) / 2.f) * camera_size;
		float right = ((window.GetWidth() / window.GetHeight()) / 2.f) * camera_size;
		float bottom = -0.5f * camera_size;
		float top = 0.5f * camera_size;
		glm::mat4 projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);


		glm::mat4 model{1.0};
		Renderer2D.DrawQuad(model, projection, sprite, glm::vec3(sprite_tint[0], sprite_tint[1], sprite_tint[2]));
		

		Cobalt::ImGUI::Render();
		glfwSwapBuffers(window.GetWindow());
	}

	Cobalt::ImGUI::ShutDown();
	window.Destroy();

	return 0;
}