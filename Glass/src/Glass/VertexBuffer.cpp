#include "VertexBuffer.h"

namespace Glass
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	}

	void VertexBuffer::UpdateBuffer(GLsizei buffer_size, void* buffer_data, const GLenum usage)
	{
		m_BufferSize = buffer_size;
		m_BufferData = buffer_data;
		m_BufferUsage = usage;

		glBufferData(GL_ARRAY_BUFFER, buffer_size, m_BufferData, m_BufferUsage);
	}

	void VertexBuffer::BindBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	}

	void VertexBuffer::UnbindBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
		m_BufferSize = NULL;
		glDeleteBuffers(1, &m_Buffer);
	}
}

