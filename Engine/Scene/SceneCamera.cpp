#include "SceneCamera.h"

namespace Cobalt
{
	SceneCamera::SceneCamera() { RecalculateProjection(); }

	void SceneCamera::SetAspectRatio(float windowWidth, float windowHeight)
	{
		m_aspectRatio = windowWidth / windowHeight;
		RecalculateProjection();
	}

	void SceneCamera::SetProjectionType(ProjectionType type)
	{
		m_projectionType = type;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_projectionType == ProjectionType::Perspective) {
			m_projection = glm::perspective(m_perspectiveFOV, m_aspectRatio, m_perspectiveNear, m_perspectiveFar);
		}
		else {
			float left = -(m_aspectRatio / 2.0f) * m_orthographicSize;
			float right = (m_aspectRatio / 2.0f) * m_orthographicSize;
			float bottom = -m_orthographicSize / 2.0f;
			float top = m_orthographicSize / 2.0f;
			m_projection = glm::ortho(left, right, bottom, top, m_orthographicNear, m_orthographicFar);
		}
	}
}