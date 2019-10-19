#pragma once

#include "Logger.h"
#include "OpenGLShader.h"
#include "Mesh.h"
#include "OrthographicCamera.h"
#include "Vertex.h"

namespace Glass
{
	class RendererCommands
	{
	public:
		static void Init() 
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}

		static void Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}

		static void DrawArrays(VertexArray& vertexArray, const size_t indexCount, GLsizei numInstances = 1)
		{
			if (indexCount >= 6)
			{
				if (vertexArray.GetVertexArray() != NULL)
				{
					vertexArray.BindVertexArray();

					numInstances == 1 ? glDrawArrays(GL_TRIANGLES, 0, indexCount) :
						glDrawArraysInstanced(GL_TRIANGLES, 0, indexCount, numInstances);
				}
				else
				{
					LOG_ERROR("[ARRAY DRAW CALL] Vertex Array is NULL");
					return;
				}
			}
			else
				LOG_ERROR("[ARRAY DRAW CALL] Not Enough Indices to Draw");
		}

		static void DrawIndexed(VertexArray& vertexArray, const size_t indexCount, GLsizei numInstances = 1)
		{
			if (indexCount >= 6)
			{
				if (vertexArray.GetVertexArray() != NULL)
				{
					vertexArray.BindVertexArray();

					numInstances == 1 ? glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0) : 
						glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0, numInstances);
				}
				else
				{
					LOG_ERROR("[INDEXED DRAW CALL] Vertex Array is NULL");
					return;
				}
			}
			else 
				LOG_ERROR("[INDEXED DRAW CALL] Not Enough Indices to Draw");
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
	public:
		virtual void Init(std::shared_ptr<Glass::OpenGLShader>& shader);
		virtual void Begin(OrthographicCamera& camera);
		virtual void End();
		virtual void Submit(const std::shared_ptr<Object>& obj, const std::shared_ptr<Glass::OpenGLShader>& shader);

		virtual void Destroy() = 0;
	};
}



