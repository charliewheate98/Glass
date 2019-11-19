#pragma once

#include <glm.hpp>
#include "OpenGLShader.h"
#include "Shader.h"

namespace Glass 
{
	class GLASS_API TextShader : public Shader
	{
	public:
		TextShader();
		~TextShader();

		void SetColour(glm::vec3& col);

		void LoadUniforms() override;
		void UseShader() override;
	private:
		GLuint m_LocColour;
		GLuint m_LocViewProjection;
		GLuint m_Transform;
	};
}



