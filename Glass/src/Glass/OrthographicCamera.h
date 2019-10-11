#pragma once

#include "pch.h"
#include "Core.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Glass
{
	class GLASS_API OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera();

		glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(glm::vec3& Position) { m_Position = Position; RecalculateViewMatrix(); }

		void SetProjectionMatrix(float left, float right, float bottom, float top);

		glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.f;
	};
}


