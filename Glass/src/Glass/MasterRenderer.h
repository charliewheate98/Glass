#pragma once

#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Glass
{
	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec2 uv;
	};

	#define RENDERER_MAX_MESHES 5000
	#define RENDERER_VERTICES_SIZE sizeof(VertexData)
	#define RENDERER_MESH_SIZE RENDERER_VERTICES_SIZE * 4
	#define RENDERER_BUFFER_SIZE RENDERER_MESH_SIZE * RENDERER_MAX_MESHES 
	#define RENDERER_MAX_INDICES RENDERER_MESH_SIZE * 6

	#define SHADER_POSITION_ATTRIB 0
	#define SHADER_UV_ATTRIB 1

	class GLASS_API MasterRenderer
	{
	public:
		void Init();
		void Begin();
		void Submit(const Object& obj);
		void End();
		void Flush();
	private:
		GLsizei m_IndexCount;
		
		VertexData* m_VertexData;

		unsigned int m_Vao;
		unsigned int m_Vbo;
		unsigned int m_Ibo;
	};
}



