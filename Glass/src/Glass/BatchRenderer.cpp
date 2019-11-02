#include "BatchRenderer.h"

namespace Glass
{
	void BatchRenderer::Init(std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		m_Shader = shader;

		m_SceneData.loc_view = m_Shader->LoadUniform("m_ViewProjection");
		m_SceneData.loc_Transform = m_Shader->LoadUniform("m_Transform");

		glGenVertexArrays(1, &m_Vao);
		glGenBuffers(1, &m_Vbo);

		glBindVertexArray(m_Vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer::Prepare()
	{
		m_Batches.clear();
		m_Glyphs.clear();
	}

	void BatchRenderer::SubmitData(glm::vec2 position, glm::vec2 dimensions)
	{
		Glyph glyph;

		glyph.m_Vertices[0] = Vertex(glm::vec3(position.x, position.y, 0.0f), glm::vec2(1.0f, 1.0f));
		glyph.m_Vertices[1] = Vertex(glm::vec3(position.x, position.y + dimensions.y, 0.0f), glm::vec2(1.0f, 0.0f));
		glyph.m_Vertices[2] = Vertex(glm::vec3(position.x + dimensions.x, position.y + dimensions.y, 0.0f), glm::vec2(0.0f, 0.0f));

		glyph.m_Vertices[3] = Vertex(glm::vec3(position.x, position.y, 0.0f), glm::vec2(1.0f, 1.0f));
		glyph.m_Vertices[4] = Vertex(glm::vec3(position.x + dimensions.x, position.y, 0.0f), glm::vec2(1.0f, 0.0f));
		glyph.m_Vertices[5] = Vertex(glm::vec3(position.x + dimensions.x, position.y + dimensions.y, 0.0f), glm::vec2(0.0f, 0.0f));

		m_Glyphs.push_back(glyph);
	}

	void BatchRenderer::UploadData()
	{		
		std::vector<Vertex> m_Vertices;

		m_Vertices.resize(m_Glyphs.size() * 6);

		int offset = 0;
		int currentVertex = 0;

		m_Batches.emplace_back(offset, 6);

		m_Vertices[currentVertex++] = m_Glyphs[0].m_Vertices[0];
		m_Vertices[currentVertex++] = m_Glyphs[0].m_Vertices[1];
		m_Vertices[currentVertex++] = m_Glyphs[0].m_Vertices[2];
		m_Vertices[currentVertex++] = m_Glyphs[0].m_Vertices[3];
		m_Vertices[currentVertex++] = m_Glyphs[0].m_Vertices[4];
		m_Vertices[currentVertex++] = m_Glyphs[0].m_Vertices[5];

		offset += 6;

		for (unsigned int i = 1; i < m_Glyphs.size(); ++i)
		{
			m_Batches.back().m_NumVertices += 6;

			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[0];
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[1];
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[2];
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[3];
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[4];
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[5];

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0]);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer::Render(OrthographicCamera& camera)
	{
		m_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();

		// TEMP
		glm::mat4 m = glm::translate(glm::mat4(1.f), glm::vec3(1920.f / 2, 1080.f / 2, 0.0f))
			* glm::scale(glm::mat4(1.f), glm::vec3(512.f, 512.f, 0.f));
		//

		m_Shader->Bind();

		m_Shader->SetMatrix4(m_SceneData.loc_view, m_SceneData.ViewProjectionMatrix);
		m_Shader->SetMatrix4(m_SceneData.loc_Transform, m);

		glBindVertexArray(m_Vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

		for (unsigned int i = 0; i < m_Batches.size(); ++i)
		{
			glDrawArrays(GL_TRIANGLES, m_Batches[i].m_Offset, m_Batches[i].m_NumVertices);
		}
	}
}