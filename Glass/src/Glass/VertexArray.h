#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		GLuint& GetVertexArray() { return m_VertexArray; }

		void BindVertexArray();
	private:
		GLuint m_VertexArray = { 0 };
	};
}



