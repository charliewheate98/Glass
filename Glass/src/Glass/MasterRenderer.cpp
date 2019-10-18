#include "MasterRenderer.h"

namespace Glass
{
	void MasterRenderer::Init()
	{
		glGenVertexArrays(1, &m_Vao);
		glBindVertexArray(m_Vao);

		glGenBuffers(GL_ARRAY_BUFFER, &m_Vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, 0, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(SHADER_POSITION_ATTRIB);
		glEnableVertexAttribArray(SHADER_UV_ATTRIB);
		glVertexAttribPointer(SHADER_POSITION_ATTRIB, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTICES_SIZE, 0);
		glVertexAttribPointer(SHADER_UV_ATTRIB, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTICES_SIZE, (void*)(3 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		uint8_t offset = 0;
		GLuint indices[RENDERER_MAX_INDICES];

		/*for (unsigned int i = 0; i < RENDERER_MAX_INDICES; i += 6)
		{
			indices[  i  ] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;

			std::cout << indices[i] << std::endl;
		}

		glGenBuffers(1, &m_Ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_MAX_INDICES, indices, GL_STATIC_DRAW);

		glBindVertexArray(0);*/
	}

	void MasterRenderer::Begin()
	{
	}

	void MasterRenderer::Submit(const Object& obj)
	{
	}

	void MasterRenderer::End()
	{
	}

	void MasterRenderer::Flush()
	{
	}
}