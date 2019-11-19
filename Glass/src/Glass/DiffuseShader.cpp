#include "DiffuseShader.h"

namespace Glass
{
	DiffuseShader::DiffuseShader()
	{
		m_Shader = std::make_unique<OpenGLShader>("Content/Shaders/basic.vs", "Content/Shaders/basic.fs");
	}

	DiffuseShader::~DiffuseShader(){}

	void DiffuseShader::LoadUniforms()
	{
		loc_lightPos = m_Shader->LoadUniform("m_LightPos");
		
		for (uint32_t i = 0; i < 2; ++i)
		{
			loc_DiffuseTex[i] = m_Shader->LoadUniform(("m_Diffuse[" + std::to_string(i) + "]").c_str());
		}
	}

	void DiffuseShader::SetSampler2D(int index, int id)
	{
		m_Shader->SetInt(loc_DiffuseTex[index], id);
	}

	void DiffuseShader::SetTestLightPos(glm::vec2 light_pos)
	{
		m_Shader->SetVector2(loc_lightPos, light_pos);
	}

	void DiffuseShader::UseShader()
	{
		glm::vec3 green(0.0f, 1.0f, 0.0f);

		m_Shader->Bind();
		m_Shader->SetVector3(m_Shader->LoadUniform("materialBlock.Color"), green);
	}
}