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
		GLuint  m_Buffer;
		GLsizei m_BufferSize;
		void*   m_BufferData;
	public: 
		Buffer() :
			m_BufferData(nullptr),
			m_BufferUsage(NULL),
			m_Buffer(NULL),
			m_BufferSize(NULL)
		{}
		virtual ~Buffer() { 
			if(m_BufferData)
				delete m_BufferData; 
			
			glDeleteBuffers(1, &m_Buffer);
		}

		/*
			Upload data to the buffer
		*/
		void UploadSubData(const GLenum buffer_type, void* buffer_data, GLint offset)
		{
			glBufferSubData(buffer_type, offset, m_BufferSize, buffer_data);
		}

		/*
			Pure Virtuals
		*/
		virtual void BindBuffer()   = 0;

		/*
			Getters
		*/
		inline GLuint &  GetBuffer()			   { return m_Buffer;     }
		inline constexpr GLsizei & GetBufferSize() { return m_BufferSize; }
		inline void *    GetBufferData()           { return m_BufferData; }
	};
}



