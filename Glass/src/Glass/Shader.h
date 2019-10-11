#pragma once

#include "pch.h"
#include "Core.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
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

		GLuint LoadUniform(const std::string& name);

		void SetInt(GLint loc, int val) const;
		void SetBool(GLint loc, bool val) const;
		void SetVector3(GLint loc, glm::vec3 &vec) const;
		void SetMatrix4(GLint loc, glm::mat4 mat) const;
		 
		void CheckCompileErrors(int shader, std::string type);
		void Bind();
	};
}