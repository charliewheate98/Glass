#include "IndexBuffer.h"

namespace Glass
{
	IndexBuffer::IndexBuffer(GLsizei buffer_size, const void* buffer_data, GLenum usage)
	{
		m_Size = buffer_size;

		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, buffer_data, usage);
	}

	IndexBuffer::~IndexBuffer()
	{
		m_Size = NULL;
		glDeleteBuffers(1, &m_Buffer);
	}

	void IndexBuffer::BindBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffer);
	}
}