#include "OpenGLShader.h"

namespace Glass
{
	OpenGLShader::OpenGLShader(const char* vs, const char* fs) :
		shader_name("No-Name-Given")
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

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(program);
	}

	GLuint OpenGLShader::LoadUniform(const std::string& name)
	{
		return glGetUniformLocation(program, name.c_str());
	}

	void OpenGLShader::SetInt(GLint loc, int val) const
	{
		glUniform1i(loc, val);
	}

	void OpenGLShader::SetFloat(GLint loc, float val) const
	{
		glUniform1f(loc, val);
	}

	void OpenGLShader::SetBool(GLint loc, bool val) const
	{
		SetInt(loc, val);
	}

	void OpenGLShader::SetVector2(GLint loc, glm::vec2 vec) const
	{
		glUniform2f(loc, vec.x, vec.y);
	}

	void OpenGLShader::SetVector3(GLint loc, glm::vec3 &vec) const
	{
		glUniform3f(loc, vec.x, vec.y, vec.z);
	}

	void OpenGLShader::SetMatrix4(GLint loc, glm::mat4 mat) const
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void OpenGLShader::CheckCompileErrors(int shader, std::string type)
	{
		int success;
		char infoLog[1024];

		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cerr << "ERROR::SHADER_COMPILATION of type " << type << " " << infoLog << std::endl;
			}
		}
		else
		{
			glGetShaderiv(shader, GL_LINK_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cerr << "EERROR::SHADER_LINKING of type " << type << " " << infoLog << std::endl;
			}
		}
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(program);
	}
}


