#pragma once

#include "Core.h"
#include <glm.hpp>
#include <gtx/transform.hpp>

#pragma warning(disable:4251)

namespace Glass
{
	enum OBJECT_TYPE
	{
		STATIC_SPRITE,
		ANIM_SPRITE
	};

	class GLASS_API Object
	{
	protected:
		uint32_t m_ObjectType;

		glm::mat4 m_Transform;
		glm::vec3 m_Position;
		glm::vec3 m_Scale = { 256.f, 256.f, 0.f };
	public:
		Object() {}
		virtual ~Object() {}

		inline uint32_t& GetObjectType() { return m_ObjectType; }
		inline glm::mat4 & GetTransform() { return m_Transform; }
		inline glm::vec3 & GetPosition()  { return m_Position;  }
		inline glm::vec3 & GetScale()     { return m_Scale;     }

		inline void SetObjectType(uint32_t ObjType)
		{
			m_ObjectType = ObjType;
		}

		inline void SetTransformationMatrix()
		{
			m_Transform = glm::translate(glm::mat4(1.f), glm::vec3(m_Position.x, m_Position.y, m_Position.z)) *
						  glm::scale(glm::mat4(1.f), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));
		}

		virtual void Tick(float DeltaTime) {}
		virtual void Render() {}
	};
}


