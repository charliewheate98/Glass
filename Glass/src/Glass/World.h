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
		static void PushShader(std::shared_ptr<Glass::OpenGLShader> shader, const std::string& name)
		{
			static std::mutex m_Mutex;

			std::lock_guard<std::mutex> lock(m_Mutex);
			shader->SetShaderName(name);
			m_Shaders.push_back(shader);
			Glass::ShaderLibrary::Add(shader);
		}
		
		static void PushObject(std::shared_ptr<Glass::Object> obj)
		{
			static std::mutex m_Mutex;

			std::lock_guard<std::mutex> lock(m_Mutex);
			m_Objects.push_back(obj);
		}

		static std::vector<std::shared_ptr<Glass::OpenGLShader>>& GetShaderList() { return m_Shaders; }
		static std::vector<std::shared_ptr<Glass::Object>>& GetObjectList() { return m_Objects; }
	private:
		static std::vector<std::shared_ptr<Glass::OpenGLShader>> m_Shaders;
		static std::vector<std::shared_ptr<Glass::Object>> m_Objects;
	};
}