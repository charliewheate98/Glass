#pragma once

#include "pch.h"
#include "Core.h"
#include "Logger.h"

namespace Glass
{
	class GLASS_API Buffer
	{
	protected:
		GLenum  m_BufferUsage;
		GLuint  m_Buffer = { 0 };
		GLsizei m_BufferSize = { 0 };
		void*   m_BufferData;
	public:
		Buffer() {}
		~Buffer() {}

		/*
			Upload data to the buffer
		*/
		void UploadData(const GLenum buffer_type, void* buffer_data, GLint offset)
		{
			glBufferSubData(buffer_type, offset, m_BufferSize, buffer_data);
		}

		/*
			Pure Virtuals
		*/
		virtual void UnbindBuffer() = 0;
		virtual void BindBuffer()   = 0;

		/*
			Getters
		*/
		inline GLuint&  GetBuffer()     { return m_Buffer;     }
		inline GLsizei& GetBufferSize() { return m_BufferSize; }
		inline void*    GetBufferData() { return m_BufferData; }
	};
}



