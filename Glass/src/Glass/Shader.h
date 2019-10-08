#pragma once

#include "pch.h"
#include "Maths.h"
#include "Core.h"
#include <GL/glew.h>

namespace Glass
{
	class GLASS_API Shader
	{
	private:
		GLuint program;
	public:
		Shader(const char* vs, const char* fs);
		~Shader();

		GLuint LoadUniform(const char& name);

		void SetInt(GLint loc, int val) const;
		void SetBool(GLint loc, bool val) const;
		void SetVector3(GLint loc, Glass::Vector4& vec) const;
		void SetMatrix4(GLint loc, Glass::Matrix4& mat) const;
		 
		void CheckCompileErrors(int shader, std::string type);
		void Bind();
	};
}