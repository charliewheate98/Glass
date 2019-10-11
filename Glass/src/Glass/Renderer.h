#pragma once

#include "Core.h"
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
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
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
		};

		static UniqueScope<SceneData> m_SceneData;
	public:
		static void Init();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Object>& obj, const std::shared_ptr<Glass::Shader>& shader, const glm::mat4& transform);
	};
}



