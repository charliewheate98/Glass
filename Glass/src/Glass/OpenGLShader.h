#pragma once

#include <unordered_map>
#include "pch.h"
#include "Core.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <GL/glew.h>

#pragma warning(disable:4251)
#pragma warning(disable:4715)

namespace Glass
{
	class GLASS_API OpenGLShader
	{
	private:
		GLuint program;
		std::string shader_name;
	public:
		OpenGLShader(const char* vs, const char* fs);
		~OpenGLShader();

		GLuint& GetProgram() { return program; }

		const std::string & GetShaderName() { return shader_name; }
		void SetShaderName(const std::string& name) { shader_name = name; }

		GLuint LoadUniform(const std::string& name);

		void SetInt(GLint loc, int val) const;
		void SetFloat(GLint loc, float val) const;
		void SetBool(GLint loc, bool val) const;
		void SetVector2(GLint loc, glm::vec2 vec) const;
		void SetVector3(GLint loc, glm::vec3 &vec) const;
		void SetMatrix4(GLint loc, glm::mat4 mat) const;
		 
		void CheckCompileErrors(int shader, std::string type);
		void Bind();
	};
}