#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API Shader
	{
	public:
		Shader() {}
		~Shader() {}

		const std::shared_ptr<OpenGLShader>& GetCoreShader() const { return m_Shader; }

		virtual void LoadUniforms() = 0;
		virtual void UseShader() = 0;
	protected:
		std::shared_ptr<OpenGLShader> m_Shader;
	};
}