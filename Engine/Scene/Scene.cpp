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
	}

	entt::entity Scene::CreateEntity(std::string name)
	{
		entt::entity entity = m_Registry.create();

		std::string tagName = name.empty() ? "Entity" : name;
		m_Registry.emplace<TagComponent>(entity, tagName);
		TransformComponent transform;
		m_Registry.emplace<TransformComponent>(entity, transform);

		return entity;
	}

	void Scene::Update(float deltaTime)
	{
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