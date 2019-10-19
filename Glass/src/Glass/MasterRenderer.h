#pragma once

#include "pch.h"
#include "Core.h"
#include "Mesh.h"
#include "Texture.h"
#include "OrthographicCamera.h"
#include "OpenGLShader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Glass
{
	class GLASS_API MasterRenderer
	{
	public:
		void Init(std::shared_ptr<Glass::OpenGLShader>& shader);
		void ProcessMesh(std::shared_ptr<Mesh> obj, glm::mat4 transform);
		void Begin(OrthographicCamera& camera);
		void Flush();
	private:
		std::map<std::shared_ptr<Mesh>, std::vector<glm::mat4>> m_MeshRenderBuffer;
		std::shared_ptr<Glass::OpenGLShader> m_Shader;
		
		SharedScope<Glass::Texture2D> m_Texture;

		unsigned int vertexCount;

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;

			GLuint loc_view;
			GLuint loc_Transform;
			GLuint loc_Diffuse;
		};
		SceneData m_SceneData;
	};
}



