#pragma once

#include "pch.h"
#include "Core.h"
#include "Renderer.h"
#include "OpenGLShader.h"

namespace Glass
{
	/*
		This Represents a Single Mesh in the Batch
	*/
	struct Glyph
	{
		// A Mesh of course needs vertices
		Vertex m_Vertices[6];
	};

	class Batch
	{
	public:
		Batch(GLshort offset, GLuint num_vertices) :
			m_Offset(offset),
			m_NumVertices(num_vertices) {}
		~Batch() {}

		GLshort m_Offset;
		GLuint  m_NumVertices;
	};

	class GLASS_API BatchRenderer 
	{
	public:
		BatchRenderer() {}
		~BatchRenderer() {}

		void Init(std::shared_ptr<Glass::OpenGLShader>& shader);
		void Prepare();
		void SubmitData(glm::vec2 position, glm::vec2 dimensions);
		void UploadData();
		void Render(OrthographicCamera& camera);

		unsigned int& GetVao() { return m_Vao; }
		unsigned int& GetVbo() { return m_Vbo; }
	private:
		// TEMP!!! ///////////////////
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;

			GLuint loc_view;
			GLuint loc_Transform;
		};
		SceneData m_SceneData;
		//////////////////////////

		std::vector<Batch> m_Batches;
		std::vector<Glyph> m_Glyphs;

		std::shared_ptr<Glass::OpenGLShader> m_Shader;

		unsigned int m_Vao;
		unsigned int m_Vbo;
	};
}



