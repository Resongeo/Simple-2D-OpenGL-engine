#include "Scene.h"

#include "imgui.h"

namespace Cobalt
{
	Scene::Scene(const char* name, Window& window) : m_name(name), m_window(window)
	{
		Shader defaultShader("resources/shaders/Default.vert", "resources/shaders/Default.frag");
		Sprite defaultSprite("resources/sprites/uv_grid.png");

		m_Renderer2D = new Renderer(defaultShader, defaultSprite);
		m_Renderer2D->Init();

		/* Temp code */
		int entityIndex = 0;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				entt::entity entity = m_Registry.create();

				std::ostringstream name;
				name << "Entity " << entityIndex;

				m_Registry.emplace<TagComponent>(entity, name.str());
				TransformComponent transform;
				transform.Location = glm::vec3((float)j, (float)i, -1.0f);
				transform.Scale = glm::vec3(0.8f);
				m_Registry.emplace<TransformComponent>(entity, transform);

				entityIndex++;
			}
		}

	}

	void Scene::Update(float deltaTime)
	{
		SceneCamera.RecalculateProjection();
		SceneCamera.SetAspectRatio(m_window.GetWidth(), m_window.GetHeight());

		auto view = m_Registry.view<TransformComponent>();
		for (auto e : view)
		{
			auto& transform = view.get<TransformComponent>(e);
			m_Renderer2D->DrawQuad(transform.GetModel(), SceneCamera.GetProjection());
		}

		ImGui::Begin("Hierarchy");

		m_Registry.each([&](auto entity)
		{
				TagComponent& tag = m_Registry.get<TagComponent>(entity);
				ImGui::Text("%s", tag.Name.c_str());
		});

		ImGui::End();
	}
}