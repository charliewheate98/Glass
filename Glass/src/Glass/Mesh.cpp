#include "Mesh.h"
#include "Vertex.h"
#include <GL/glew.h>
#include "Texture.h"
#include "OpenGLTexture.h"

GLuint VBO, VAO, EBO;

namespace Glass
{
	Mesh::Mesh(glm::vec3 position)
	{
		m_Position = position;

		m_Texture = Texture2D::Create("Content/Default.png");

		Vertex vertices[] =
		{
			Vertex(glm::vec3(0.5f,  0.5f, 0.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.0f, 1.0f))
		};

		unsigned int indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		m_VertexArray = new Glass::VertexArray();

		m_VertexArray->BindVertexArray();

		m_VertexBuffer = new Glass::VertexBuffer(5 * sizeof(Vertex), vertices, GL_STATIC_DRAW);
		m_IndexBuffer = new Glass::IndexBuffer(sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	Mesh::~Mesh() {}

	void Mesh::Tick(float DeltaTime) {}

	void Mesh::Render()
	{
		SetTransformationMatrix();

		m_Texture->Bind(0);
		m_VertexArray->BindVertexArray();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	}
}

