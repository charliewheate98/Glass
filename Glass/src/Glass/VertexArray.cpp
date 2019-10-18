#include "VertexArray.h"

namespace Glass
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArray);
	}

	void VertexArray::BindVertexArray()
	{
		glBindVertexArray(m_VertexArray);
	}
}