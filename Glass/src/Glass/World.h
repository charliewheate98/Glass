#pragma once

#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "Mesh.h"
#include "OpenGLShader.h"

namespace Glass
{
	class GLASS_API World
	{
	public:
		static void PushObject(std::shared_ptr<Glass::Object> obj)
		{
			m_Objects.push_back(obj);
		}
		static std::vector<std::shared_ptr<Glass::Object>>& GetObjectList() { return m_Objects; }
	private:
		static std::vector<std::shared_ptr<Glass::Object>> m_Objects;
	};
}