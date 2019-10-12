#pragma once

#include "pch.h"
#include "Core.h"
#include <GL/glew.h>

namespace Glass
{
	class GLASS_API OpenGLTexture
	{
	public:
		OpenGLTexture(const std::string& filename);
		~OpenGLTexture();

		void Bind();
	private:
		GLuint m_ID;
	};
}



