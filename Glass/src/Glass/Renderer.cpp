#include "Renderer.h"

namespace Glass
{
	UniqueScope<Renderer::SceneData> Renderer::m_SceneData = CreateUniqueScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		RendererCommands::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		RendererCommands::Clear();

		Renderer::m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{}

	void Renderer::Submit(const std::shared_ptr<Object>& obj, const std::shared_ptr<Glass::Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();

		shader->SetMatrix4(shader->LoadUniform("m_ViewProjection"), Renderer::m_SceneData->ViewProjectionMatrix);
		shader->SetMatrix4(shader->LoadUniform("m_Transform"), transform);

		obj->Render();
	}
}