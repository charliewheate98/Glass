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

		inline GLuint& GetCoreBuffer() { return m_Buffer; }
		inline GLsizei& GetBufferSize() { return m_Size; }

		void BindBuffer();
	private:
		GLuint m_Buffer = { 0 };
		GLsizei m_Size = { 0 };
	};
}



