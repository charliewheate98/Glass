#include "VertexBuffer.h"

namespace Glass
{
	VertexBuffer::VertexBuffer(GLsizei buffer_size, void* buffer_data, GLenum usage) : 
		m_Size(buffer_size),
		m_Buffer_Data(buffer_data)
	{
		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		glBufferData(GL_ARRAY_BUFFER, buffer_size, buffer_data, usage);
	}

	void VertexBuffer::UpdateBuffer(GLsizei buffer_size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		glBufferData(GL_ARRAY_BUFFER, buffer_size, m_Buffer_Data, GL_STATIC_DRAW);
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

