#include "Sprite.h"
#include "Glass/Vertex.h"
#include <GL/glew.h>

GLuint VBO, VAO, EBO;

Mesh::Mesh()
{
	Vertex vertices[] =
	{
		Vertex(glm::vec3(0.5f,   0.5f, 0.0f)),
		Vertex(glm::vec3(0.5f,  -0.5f, 0.0f)),
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f)),
		Vertex(glm::vec3(-0.5f,  0.5f, 0.0f))
	};

	unsigned int indices[] = 
	{  
		0, 1, 3,  
		1, 2, 3 
	};

	gls_GEN_VERTEX_ARRAY(1, VAO);
	gls_GEN_BUFFER(1, VBO);
	gls_GEN_BUFFER(1, EBO);

	gls_BIND_VERTEX_ARRAY(VAO);

	gls_STORE_BUFFER_DATA(GL_ARRAY_BUFFER, VBO, sizeof(vertices), vertices);
	gls_STORE_BUFFER_DATA(GL_ELEMENT_ARRAY_BUFFER, EBO, sizeof(indices), indices);

	gls_SET_SHADER_ATTRIB(0, 3, 3 * sizeof(float));
	gls_ENABLE_SHADED_ATTRIB_INDEX(0);

	gls_BIND_BUFFER(GL_ARRAY_BUFFER, 0);

	gls_BIND_VERTEX_ARRAY(0);
}

Mesh::~Mesh() {}

void Mesh::Tick(float DeltaTime) {}

void Mesh::Render()
{
	gls_BIND_VERTEX_ARRAY(VAO);

	DRAW_ELEMENTS(GL_TRIANGLES, 6);
}
