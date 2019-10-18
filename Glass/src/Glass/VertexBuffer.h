#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API VertexBuffer
	{
	public:
		VertexBuffer(GLsizei buffer_size, void* buffer_data, GLenum usage);
		~VertexBuffer();

		void BindBuffer();

		inline GLuint& GetBuffer() { return m_Buffer; }
		inline GLsizei& GetBufferSize() { return m_Size; }
	private:
		GLuint m_Buffer = { 0 };
		GLsizei m_Size = { 0 };
	};
}



