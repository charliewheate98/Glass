#include "IndexBuffer.h"

namespace Glass
{
	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer);
	}

	void IndexBuffer::UpdateBuffer(GLsizei buffer_size, void* buffer_data, GLenum usage)
	{
		m_BufferUsage = usage;
		m_BufferSize = buffer_size;
		m_BufferData = buffer_data;

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, m_BufferData, m_BufferUsage);
	}

	IndexBuffer::~IndexBuffer()
	{
		m_BufferSize = NULL;
		glDeleteBuffers(1, &m_Buffer);
	}

	void IndexBuffer::BindBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer);
	}
}