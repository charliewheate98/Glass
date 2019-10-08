#include "Shader.h"
#include "Logger.h"

namespace Glass
{
	Shader::Shader(const char* vs, const char* fs)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vShaderFile.open(vs);
			fShaderFile.open(fs);
			std::stringstream vShaderStream, fShaderStream;
			
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");
	
		program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);
		
		CheckCompileErrors(program, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader() 
	{
		glDeleteProgram(program);
	}

	GLuint Shader::LoadUniform(const char& name)
	{
		return glGetUniformLocation(program, &name);
	}

	void Shader::SetInt(GLint loc, int val) const
	{
		glUniform1i(loc, val);
	}

	void Shader::SetBool(GLint loc, bool val) const
	{
		SetInt(loc, val);
	}

	void Shader::SetVector3(GLint loc, Glass::Vector4& vec) const
	{
		glUniform3f(loc, vec.x, vec.y, vec.z);
	}

	void Shader::SetMatrix4(GLint loc, Glass::Matrix4& mat) const
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat*)mat.n);
	}

	void Shader::CheckCompileErrors(int shader, std::string type)
	{
		int success;
		char infoLog[1024];

		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				LOG_ERROR("ERROR::SHADER_COMPILATION of type " + type + " " + infoLog);
			}
		}
		else
		{
			glGetShaderiv(shader, GL_LINK_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				LOG_ERROR("ERROR::SHADER_LINKING of type " + type + " " + infoLog);
			}
		}
	}

	void Shader::Bind()
	{
		glUseProgram(program);
	}
}


