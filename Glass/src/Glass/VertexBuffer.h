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

		void UpdateBuffer(GLsizei buffer_size);
		void BindBuffer();

		inline void* GetBufferData() { return m_Buffer_Data; }
		inline GLuint& GetBuffer() { return m_Buffer; }
		inline GLsizei& GetBufferSize() { return m_Size; }
	private:
		void* m_Buffer_Data;

		GLuint m_Buffer = { 0 };
		GLsizei m_Size = { 0 };
	};
}



