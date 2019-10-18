#include "VertexBuffer.h"

namespace Glass
{
	VertexBuffer::VertexBuffer(GLsizei buffer_size, void* buffer_data, GLenum usage) : 
		m_Size(buffer_size)
	{
		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		glBufferData(GL_ARRAY_BUFFER, buffer_size, buffer_data, usage);
	}

	void VertexBuffer::BindBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	}

	VertexBuffer::~VertexBuffer()
	{
		m_Size = NULL;
		glDeleteBuffers(1, &m_Buffer);
	}
}

