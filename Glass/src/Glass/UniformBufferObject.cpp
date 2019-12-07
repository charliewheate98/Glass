#include "UniformBufferObject.h"

namespace Glass 
{
	UniformBufferObject::UniformBufferObject()
	{
		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer);
	}

	void UniformBufferObject::UpdateBuffer(GLsizei buffer_size, void* buffer_data, GLenum usage)
	{
		glBufferData(GL_UNIFORM_BUFFER, buffer_size, buffer_data, usage);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_Buffer, 0, buffer_size);
	}

	void UniformBufferObject::PushBlockElement(GLuint offset, GLsizei size, void * data)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer);
		m_UniformBufferElement.emplace_back(data, size, offset);
	}

	void UniformBufferObject::BindBuffer()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer);
	}

	UniformBufferObject::~UniformBufferObject() {}
}