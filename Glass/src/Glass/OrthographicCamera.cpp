#include "OrthographicCamera.h"
#include <iostream>
#include <memory>

namespace Glass
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
		m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
		m_ViewMatrix(1.f)
	{
		m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
	}

	OrthographicCamera::~OrthographicCamera() {}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0.f, 0.f, 1.f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
	}
}