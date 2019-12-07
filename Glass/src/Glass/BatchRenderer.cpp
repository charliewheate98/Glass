#include "BatchRenderer.h"
#include "World.h"
#include "Application.h"

namespace Glass
{
	/*
		Initialise the vao and vbo and local class objects
	*/
	void BatchRenderer::Init(std::shared_ptr<Shader>& shader)
	{
		// Initialise the shader
		m_Shader = shader;

		// load in the uniforms from the shader
		m_SceneData.loc_view = m_Shader->GetCoreShader()->LoadUniform("m_ViewProjection");
		m_SceneData.loc_Transform = m_Shader->GetCoreShader()->LoadUniform("m_Transform");

		std::dynamic_pointer_cast<DiffuseShader>(m_Shader)->LoadUniforms();

		// generate the vertex array
		m_VertexArray  = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>();
		m_IndexBuffer  = std::make_unique<IndexBuffer>();

		glEnableVertexAttribArray(POSITIONS_ATTRIB);
		glVertexAttribPointer(POSITIONS_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
		glEnableVertexAttribArray(TEXCOORDS_ATTRIB);
		glVertexAttribPointer(TEXCOORDS_ATTRIB, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::_uv)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::_tid)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*
		Clear the vectors lists ready to data upload
	*/
	void BatchRenderer::Prepare()
	{
		// Clear the lists ready for data to be emplaced
		m_Batches.clear();
		m_Glyphs.clear();
	}

	/*
		Submit the geometry data
	*/
	void BatchRenderer::SubmitData(glm::vec2 position, glm::vec2 dimensions,
		glm::vec2 uv, glm::vec2 uv_dimensions, glm::vec3 colour, float id)
	{
		// create a new glyph/sprite
		Glyph glyph;

		// set the colour
		glyph.m_Colour = colour;

		// texture optimisation
		float ts = 0.f;
		bool found = false;
		if (!m_TextureSlots.empty())
		{
			for (size_t i = 0; i < m_TextureSlots.size(); ++i)
			{
				if (m_TextureSlots[i] == id)
				{
					//LOG_WARN("[Batch] Texture Slot Already Exists!");
					ts = (float)i;
					found = true;
					break;
				}
			}
		} 
		if (!found)
		{
			if (m_TextureSlots.size() >= MAX_TEXTURE_UNITS)
			{
				return;
			}

			m_TextureSlots.push_back(STATIC_CAST(int, id));
		}

		// initialise the VERTICES of the sprite
		glyph.m_Vertices[0] = Vertex(glm::vec3(position.x, position.y, 0.0f), glm::vec2(uv.x, uv.y));	glyph.m_Vertices[0]._tid = id;
		glyph.m_Vertices[1] = Vertex(glm::vec3(position.x + dimensions.x, position.y, 0.0f), glm::vec2(uv.x + uv_dimensions.x, uv.y)); glyph.m_Vertices[1]._tid = id;
		glyph.m_Vertices[2] = Vertex(glm::vec3(position.x + dimensions.x, position.y + dimensions.y, 0.0f), glm::vec2(uv.x + uv_dimensions.x, uv.y + uv_dimensions.y)); glyph.m_Vertices[2]._tid = id;
		glyph.m_Vertices[3] = Vertex(glm::vec3(position.x, position.y + dimensions.y, 0.0f), glm::vec2(uv.x, uv.y + uv_dimensions.y)); glyph.m_Vertices[3]._tid = id;

		// a the new glyph to the list
		m_Glyphs.emplace_back(glyph);
	}

	/*
		Upload all the data into the buffer
	*/
	void BatchRenderer::UploadData()
	{
		// A temporary vectorlist to store all the vertices
		static std::vector<Vertex> m_Vertices;
		static std::vector<GLuint> m_Indices;

		// initialise enough space for vertex data
		m_Vertices.resize(m_Glyphs.size() * 6);
		m_Indices.resize(m_Glyphs.size() * 6);

		// offsets
		int batch_offset = 0;
		int index_offset = 0;
		int currentVertex = 0;
		int currentIndex = 0;

		// add a new batch to the vectorlist with 6 vertices
		m_Batches.emplace_back(batch_offset, 6, 0);

		// set the vertex data for the rest of the sprites.
		for (size_t i = 1; i < m_Glyphs.size(); ++i) // O(n)
		{
			m_Batches.back().m_NumVertices += 6;

			// copy over the data of the glyphs to the vectorlist of vertices
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[0];
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[1];
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[2];
			m_Vertices[currentVertex++] = m_Glyphs[i].m_Vertices[3];

			// increment the buffer offset by 6
			batch_offset += 6;
		}

		for (size_t j = 0; j < m_Glyphs.size() * 6; j += 6) // O(n^6)
		{
			m_Indices[j] = index_offset + 0;
			m_Indices[j + 1] = index_offset + 1;
			m_Indices[j + 2] = index_offset + 3;

			m_Indices[j + 3] = index_offset + 1;
			m_Indices[j + 4] = index_offset + 2;
			m_Indices[j + 5] = index_offset + 3;

			index_offset += 4;
		}

		// Upload the data to the buffers
		m_VertexBuffer->BindBuffer();
		m_VertexBuffer->UpdateBuffer(STATIC_CAST(GLsizei, m_Vertices.size() * sizeof(Vertex)), NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0]);

		m_IndexBuffer->BindBuffer();
		m_IndexBuffer->UpdateBuffer(STATIC_CAST(GLsizei, m_Indices.size() * sizeof(GLuint)), NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_Indices.size() * sizeof(GLuint), &m_Indices[0]);
	}

	/*
		Render all the data from the buffer
	*/
	void BatchRenderer::Render(OrthographicCamera & camera)
	{
		// set the vertex projection matrix of the camera to my local matrix variable
		m_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();

		// TEMP
		glm::mat4 m = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.0f))
			* glm::scale(glm::mat4(1.f), glm::vec3(512.f, 512.f, 0.f));
		//

		// Bind the shader
		m_Shader->UseShader();

		// global uniforms
		m_Shader->GetCoreShader()->SetMatrix4(m_SceneData.loc_view, m_SceneData.ViewProjectionMatrix); // set the view projection matrix
		m_Shader->GetCoreShader()->SetMatrix4(m_SceneData.loc_Transform, m); // set the objects transforms

		// Bind the vertex array ready for drawing
		m_VertexArray->BindVertexArray();

		// Loop through all the batches and render them
		for (unsigned int i = 0; i < m_Batches.size(); ++i)
		{
			// Draw Arrays for each batch
			glDrawElements(GL_TRIANGLES, m_Batches[i].m_NumVertices, GL_UNSIGNED_INT, 0);
		}
	}
}