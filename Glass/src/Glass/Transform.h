#pragma once

#include "pch.h"
#include "Core.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Glass
{
	class GLASS_API Transform
	{
	public:
		Transform(glm::vec3 pos, glm::vec3 sca = glm::vec3(0.f), glm::vec3 rot = glm::vec3(0.f), float rotation_angle = 0.f) :
			m_Position(pos),
			m_Scale(sca),
			m_Rotation(rot),
			m_Angle(rotation_angle)
		{
			m_Model = glm::mat4(1.0f);
		}
		~Transform()
		{
			m_Model = glm::mat4(NULL);
			m_Angle = NULL;
			m_Position = glm::vec3(NULL);
			m_Scale = glm::vec3(NULL);
			m_Rotation = glm::vec3(NULL);
		}

		void RecalculateTransformationMatrix()
		{
			m_Model = glm::translate(glm::mat4(1.f), m_Position) *
					  glm::scale(glm::mat4(1.f), m_Scale); /*
					  glm::rotate(glm::mat4(1.f), m_Angle, m_Rotation);*/
		}

		operator glm::mat4() const
		{
			return m_Model;
		}

		glm::mat4& GetCoreMatrix() { return m_Model; }

		inline glm::vec3& GetPosition() { return m_Position; }
		inline glm::vec3& GetScale() { return m_Scale; }
		inline glm::vec3& GetRotation() { return m_Rotation; }
	private:
		float m_Angle = 0.f;

		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;

		glm::mat4 m_Model;
	};
}
