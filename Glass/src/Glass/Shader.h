#pragma once

#include <unordered_map>
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
		std::string shader_name;
	public:
		Shader(const char* vs, const char* fs);
		~Shader();

		const std::string& GetShaderName() { return shader_name; }
		void SetShaderName(const std::string& name) { shader_name = name; }

		GLuint LoadUniform(const std::string& name);

		void SetInt(GLint loc, int val) const;
		void SetBool(GLint loc, bool val) const;
		void SetVector3(GLint loc, glm::vec3 &vec) const;
		void SetMatrix4(GLint loc, glm::mat4 mat) const;
		 
		void CheckCompileErrors(int shader, std::string type);
		void Bind();
	};

	class GLASS_API ShaderLibrary
	{
	public:
		static void InitialiseLibrary(size_t library_size = 0)
		{
			m_Shaders.reserve(library_size);
		}
		
		static void Add(std::shared_ptr<Shader>& shader)
		{
			auto& name = shader->GetShaderName();
			m_Shaders.insert( { name, shader } );
		}

		static bool Exists(const std::string& name)
		{
			return m_Shaders.find(name) != m_Shaders.end();
		}

		static SharedScope<Shader>& Get(const std::string& name)
		{
			if (Exists(name)) return m_Shaders[name];
		}
	private:
		static std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}