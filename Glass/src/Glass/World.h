#pragma once

#include "pch.h"
#include "Core.h"
#include "OpenGLShader.h"

namespace Glass
{
	class GLASS_API World
	{
	public:
		static void PushShader(std::shared_ptr<Glass::OpenGLShader> shader, const std::string& name)
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			shader->SetShaderName(name);
			m_Shaders.push(shader);
			Glass::ShaderLibrary::Add(shader);
		}
		
		static void PushObject() {}

		static std::queue<std::shared_ptr<Glass::OpenGLShader>>& GetShaderQueue() { return m_Shaders; }
	private:
		static std::mutex m_Mutex;
		static std::queue<std::shared_ptr<Glass::OpenGLShader>> m_Shaders;
	};
}