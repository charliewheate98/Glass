#pragma once

#include "OpenGLTexture.h"
#include "Shader.h"
#include "Object.h"
#include "OrthographicCamera.h"

namespace Glass
{
	class RendererCommands
	{
	public:
		static void Init()
		{
		}

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
			GLuint loc_diffuse;
		};

		//static GLuint loc_view;
		//static GLuint loc_Transform;
		//static GLuint loc_diffuse;

		static std::shared_ptr<Glass::Shader> m_Shader;

		static OpenGLTexture* texture;

		static UniqueScope<SceneData> m_SceneData;
	public:
		static void Init(std::shared_ptr<Glass::Shader>& shader);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Object>& obj, const std::shared_ptr<Glass::Shader>& shader, const glm::mat4& transform);
	};
}



