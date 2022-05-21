#pragma once

#include "entt.hpp"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Sprite.h"

#include "Utils/Math.h"
#include "Utils/Log.h"

#include "Components.h"
#include "SceneCamera.h"

#include "Core/Window.h"

namespace Cobalt
{
	class Scene
	{
	public:
		Scene(const char* name, Window& window);

		void Update(float deltaTime);

		SceneCamera SceneCamera;

	private:
		const char* m_name;
		entt::registry m_Registry;
		Renderer* m_Renderer2D;
		Window m_window;
	};
}