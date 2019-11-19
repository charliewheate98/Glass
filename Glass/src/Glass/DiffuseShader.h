#pragma once

#include "OpenGLShader.h"
#include "Shader.h"

namespace Glass
{
	class GLASS_API DiffuseShader : public Shader
	{
	public:
		DiffuseShader();
		~DiffuseShader();
		 
		void SetSampler2D(int index, int id);
		void SetTestLightPos(glm::vec2 light_pos);

		void LoadUniforms() override;
		void UseShader() override;
	private:
		GLuint loc_DiffuseTex[32];
		GLuint loc_lightPos;
	};
}



