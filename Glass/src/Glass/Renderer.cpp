#include "Renderer.h"

namespace Glass
{
	UniqueScope<Renderer::SceneData> Renderer::m_SceneData = CreateUniqueScope<Renderer::SceneData>();
	OpenGLTexture* Renderer::texture;
	std::shared_ptr<Glass::Shader> Renderer::m_Shader;

	void Renderer::Init(std::shared_ptr<Glass::Shader>& shader)
	{
		m_Shader = shader;

		RendererCommands::Init();
	
		texture = new OpenGLTexture("Content/Default.png");

		m_SceneData->loc_view = m_Shader->LoadUniform("m_ViewProjection");
		m_SceneData->loc_Transform = m_Shader->LoadUniform("m_Transform");
		m_SceneData->loc_diffuse = m_Shader->LoadUniform("m_Diffuse");
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

		shader->SetMatrix4(m_SceneData->loc_view, Renderer::m_SceneData->ViewProjectionMatrix);
		shader->SetMatrix4(m_SceneData->loc_Transform, transform);
		shader->SetInt(m_SceneData->loc_diffuse, 0);

		texture->Bind();

		obj->Render();
	}
}