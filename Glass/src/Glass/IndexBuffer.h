#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API IndexBuffer
	{
	public:
		IndexBuffer(GLsizei buffer_size, const void* buffer_data, GLenum usage);
		~IndexBuffer();

		void BindBuffer();
	private:
		GLuint m_Buffer = { 0 };
		GLsizei m_Size = { 0 };
	};
}



