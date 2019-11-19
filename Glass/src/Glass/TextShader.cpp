#include "TextShader.h"

namespace Glass
{
	TextShader::TextShader()
	{
		m_Shader = std::make_unique<OpenGLShader>("Content/Shaders/Text.vs", "Content/Shaders/Text.fs");
	}

	TextShader::~TextShader()
	{
	}

	void TextShader::LoadUniforms()
	{
		m_LocColour         = m_Shader->LoadUniform("m_Colour");
		m_LocViewProjection = m_Shader->LoadUniform("m_ViewProjection");
		m_Transform         = m_Shader->LoadUniform("m_Transform");
	}

	void TextShader::SetColour(glm::vec3& col)
	{
		m_Shader->SetVector3(m_LocColour, col);
	}

	void TextShader::UseShader()
	{
		m_Shader->Bind();

	}
}