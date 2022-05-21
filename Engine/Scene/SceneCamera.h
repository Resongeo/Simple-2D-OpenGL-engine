#pragma once

#include "Utils/Math.h"

namespace Cobalt
{
	class SceneCamera
	{
	public:
		enum class ProjectionType {
			Perspective,
			Orthographic
		};

		SceneCamera();

		void SetAspectRatio(float windowWidth, float windowHeight);

		glm::mat4 GetProjection() const { return m_projection; }

		ProjectionType GetProjectionType() { return m_projectionType; }
		void SetProjectionType(ProjectionType type);

		void SetPerspectiveFOV(float fov) { m_perspectiveFOV = fov; }
		void SetPerspectiveNear(float nearClip) { m_perspectiveNear = nearClip; }
		void SetPerspectiveFar(float farClip) { m_perspectiveFar = farClip; }

		void SetOrthographicSize(float size) { m_orthographicSize = size; }
		float GetOrthographicSize() const { return m_orthographicSize; }

	private:
		void RecalculateProjection();

		glm::mat4 m_projection{ 1.0f };
		ProjectionType m_projectionType = ProjectionType::Orthographic;

		float m_aspectRatio = 1.7777f; // Approximately 16:9 aspect ratio

		/* Perspective vars */

		float m_perspectiveFOV = 45.0f;
		float m_perspectiveNear = 0.05f;
		float m_perspectiveFar = 100.0f;

		/* Orthographic vars */

		float m_orthographicSize = 2.0f;
		float m_orthographicNear = -1.0f;
		float m_orthographicFar = 1.0f;
	};
}