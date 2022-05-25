#include "ImGui_CobaltEngine_Impl.h"

#include "Core/Cobalt.h"
#include "Core/Window.h"

#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/Framebuffer.h"

#include "Scene/Scene.h"


float deltaTime;
float lastFrame;

float fpsRefreshInterval = 0.5f;
float nextTimeToRefreshFPS = 1.0f;
float fpsCounter = 0.0f;

float camera_size = 2.f;
float camera_fov = 70.0f;

float bg_col[3] = { 0.15f, 0.16f, 0.17f };

bool showDemoWindow = false;

ImVec2 viewportSize{ 0.0f, 0.0f };

int main()
{
	Cobalt::Log::Init();
	Cobalt::Window window(1920, 1080, "Cobalt Engine");
	window.SetVsync(false);

	Cobalt::Shader defaultShader("resources/shaders/Default.vert", "resources/shaders/Default.frag");
	Cobalt::Sprite defaultSprite("resources/sprites/uv_grid.png");

	Cobalt::Renderer Renderer2D(defaultShader, defaultSprite);
	Renderer2D.Init();

	Cobalt::Framebuffer FrameBuffer((int)window.GetWidth(), (int)window.GetHeight());
	FrameBuffer.Create();

	Cobalt::ImGUI::Init(window.GetWindow());
	Cobalt::ImGUI::SetupStyle();

	Cobalt::Scene StarterScene("Startup", window);

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

		FrameBuffer.Bind();

		glClearColor(bg_col[0], bg_col[1], bg_col[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwPollEvents();
		Cobalt::ImGUI::NewFrame();

		#pragma region ImGui

		{
			ImGui::Begin("Test window");

			ImGui::Text("Colors");
			ImGui::ColorEdit3("Background", bg_col);

			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Text("Scene Camera");

			const char* projection_types[] = {"Perspective", "Orthographic"};
			static int index = 1;
			ImGui::Combo("Projection", &index, projection_types, IM_ARRAYSIZE(projection_types));

			if (index == 0) {
				StarterScene.SceneCamera.SetProjectionType(Cobalt::SceneCamera::ProjectionType::Perspective);
				ImGui::SliderFloat("FOV", &camera_fov, 45.f, 90.f);
				StarterScene.SceneCamera.SetPerspectiveFOV(camera_fov);
			}
			else {
				StarterScene.SceneCamera.SetProjectionType(Cobalt::SceneCamera::ProjectionType::Orthographic);
				ImGui::SliderFloat("Size", &camera_size, 1.f, 10.f);
				StarterScene.SceneCamera.SetOrthographicSize(camera_size);
			}

			ImGui::Text("");
			ImGui::Checkbox("Show demo window", &showDemoWindow);

			if (ImGui::Button("Create Entity")) {
				StarterScene.CreateEntity("Entity");
			}
			
			ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 25);
			ImGui::Text(("FPS: " + std::to_string((int)fpsCounter)).c_str());

			ImGui::End();
		}

		{
			ImGui::Begin("Viewport");
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
			StarterScene.SceneCamera.SetAspectRatio(viewportPanelSize.x, viewportPanelSize.y);
			if (viewportSize.x != viewportPanelSize.x && viewportSize.y != viewportPanelSize.y) {
				viewportSize = viewportPanelSize;
				FrameBuffer.Resize(viewportPanelSize.x, viewportPanelSize.y);
			}

			ImGui::Image((void*)FrameBuffer.GetColorbuffer(), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

			ImGui::End();
		}

		if (showDemoWindow) ImGui::ShowDemoWindow();

		#pragma endregion
		
		StarterScene.Update(deltaTime);
		FrameBuffer.Unbind();

		Cobalt::ImGUI::Render();
		glfwSwapBuffers(window.GetWindow());
	}

	Cobalt::ImGUI::ShutDown();
	window.Destroy();

	return 0;
}