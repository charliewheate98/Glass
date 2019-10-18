#include "Renderer.h"

#define MAX_SPRITES 1000

namespace Glass
{
	void Renderer::Init(std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		m_Shader = shader;

		RendererCommands::Init();

		m_SceneData.loc_view = m_Shader->LoadUniform("m_ViewProjection");
		m_SceneData.loc_Transform = m_Shader->LoadUniform("m_Transform");
		m_SceneData.loc_Diffuse = m_Shader->LoadUniform("m_Diffuse");
	}

	void Renderer::Begin(OrthographicCamera& camera)
	{
		RendererCommands::Clear();

		m_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::End()
	{}

	void Renderer::Submit(const std::shared_ptr<Object>& obj, const std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		shader->Bind();

		shader->SetInt(m_SceneData.loc_Diffuse, 0);
		shader->SetMatrix4(m_SceneData.loc_view, m_SceneData.ViewProjectionMatrix);
		shader->SetMatrix4(m_SceneData.loc_Transform, obj->GetTransform());

		obj->Render();
	}
}