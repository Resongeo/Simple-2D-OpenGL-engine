#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

#include "Utils/Math.h"

namespace Cobalt
{
	struct TagComponent
	{
		const char* Name;
		TagComponent(const char* name) : Name(name) {}
	};

	struct TransformComponent
	{
		glm::vec3 Location	{ 0.0f };
		glm::vec3 Rotation	{ 0.0f };
		glm::vec3 Scale		{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 location) : Location(location) {}

		glm::mat4 GetModel() const
		{
			return glm::translate(glm::mat4(1.0f), Location) * glm::toMat4(glm::quat(Rotation)) * glm::scale(glm::mat4(1.0f), Scale);
		}
	};
}