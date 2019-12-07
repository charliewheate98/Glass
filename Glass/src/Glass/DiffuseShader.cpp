#include "DiffuseShader.h"

namespace Glass
{
	DiffuseShader::DiffuseShader()
	{
		m_Shader = std::make_unique<OpenGLShader>("Content/Shaders/basic.vs", 
												  "Content/Shaders/basic.fs");
	}

	DiffuseShader::~DiffuseShader(){}

	void DiffuseShader::LoadUniforms()
	{
		// temp
		for (uint32_t i = 0; i < 2; ++i)
			loc_DiffuseTex[i] = m_Shader->LoadUniform(("m_Diffuse[" + std::to_string(i) + "]").c_str());
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
		m_Shader->Bind();
	}
}