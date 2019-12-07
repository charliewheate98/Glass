#pragma once

#include "pch.h"
#include "Core.h"
#include "Renderer.h"
#include "DiffuseShader.h"

namespace Glass
{
	/*
		This Represents a Single Mesh in the Batch
	*/
	struct Glyph
	{
		// A Mesh of course needs vertices
		Vertex    m_Vertices[4];

		// Indices
		GLuint    m_Indices[6];

		glm::vec3 m_Colour;
	};

	#define MAX_INDICES 1000

	/*
		This handles a single batch of sprites/vertices
	*/
	class Batch
	{
	public:
		/*
			Constructer.
		*/
		Batch(GLshort offset, GLuint num_vertices, int atlas_index) :
			m_Offset(offset), 
			m_NumVertices(num_vertices),
			m_AtlasIndex(atlas_index)
		{}
		
		/*
			Destructer.
		*/
		~Batch() {}

		// Public Local Variables
		GLshort m_Offset; // Offset in the buffer
		GLuint  m_NumVertices; // Number of vertices in the batch
		int m_AtlasIndex;
	};

	/*
		Batch Renderer/Manager. This class handles storing all the data (vertices, texcoords, indices, etc) into the buffer and then draws all the 
		contents of the buffer
	*/
	class GLASS_API BatchRenderer : public Renderer
	{
	public:
		/*
			Constructer.
		*/
		BatchRenderer() {}

		/*
			Destructer
		*/
		~BatchRenderer() 
		{
			m_Batches.clear();
			m_TextureSlots.clear();
			m_Glyphs.clear();
		}

		/*
			Initialise the vao and vbo and local class objects
		*/
		void Init(std::shared_ptr<Shader>& shader);

		
		/*
			Clear the vectors lists ready to data upload
		*/
		void Prepare();
		
		/*
			Submit the geometry data
		*/
		void SubmitData(glm::vec2 position, glm::vec2 dimensions, 
						glm::vec2 uv, glm::vec2 uv_dimensions, glm::vec3 colour, float id);
		
		/*
			Upload all the data into the buffer
		*/
		void UploadData();

		/*
			Render all the data from the buffer
		*/
		void Render(OrthographicCamera & camera);

		/*
			Get the list of glyphs/sprites in the batch.
		*/
		std::vector<Glyph>& GetGlyphs() { return m_Glyphs; }
	private:
		// vector list of batches
		std::vector<Batch> m_Batches;

		// vectorlist of glyph's/sprites within the batch
		std::vector<Glyph> m_Glyphs;

		std::vector<int> m_TextureSlots;

		// Shader
		std::shared_ptr<Shader> m_Shader;
		std::unique_ptr<DiffuseShader> m_DiffuseShader;

		// Arrays & Buffer Objects
		std::unique_ptr<VertexArray>  m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer>  m_IndexBuffer;
	};
}



