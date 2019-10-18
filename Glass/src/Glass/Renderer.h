#pragma once

#include "OpenGLShader.h"
#include "Mesh.h"
#include "OrthographicCamera.h"
#include "Vertex.h"

namespace Glass
{
	class RendererCommands
	{
	public:
		static void Init() {}
		static void Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}
	private:
	};

	class GLASS_API Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;

			GLuint loc_view;
			GLuint loc_Transform;
			GLuint loc_Diffuse;
		};
		SceneData m_SceneData;

		std::shared_ptr<Glass::OpenGLShader> m_Shader;

		VertexArray* m_VertexArray;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;

		unsigned int m_Buffer;
	public:
		void Init(std::shared_ptr<Glass::OpenGLShader>& shader);
		void Begin(OrthographicCamera& camera);
		void End();
		void Submit(const std::shared_ptr<Object>& obj, const std::shared_ptr<Glass::OpenGLShader>& shader);
	};
}



