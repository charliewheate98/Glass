#include "Renderer.h"
#include "EntityMesh.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Glass
{
	GLuint loc_numRows;
	GLuint loc_offset;

	void Renderer::Init(std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		m_Shader = shader;

		RendererCommands::Init();

		m_SceneData.loc_view = m_Shader->LoadUniform("m_ViewProjection");
		m_SceneData.loc_Transform = m_Shader->LoadUniform("m_Transform");
		m_SceneData.loc_Diffuse = m_Shader->LoadUniform("m_Diffuse");
	
		loc_numRows = m_Shader->LoadUniform("m_NumberOfRows");
		loc_offset = m_Shader->LoadUniform("m_Offset");
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
		static auto& NumberOfRows  = SMART_CAST(OpenGLTexture, std::dynamic_pointer_cast<EntityMesh>(obj)->GetTexture())->GetNumberOfRows();

		shader->Bind();
		 
		shader->SetInt(m_SceneData.loc_Diffuse,		    0);
		shader->SetMatrix4(m_SceneData.loc_view,	    m_SceneData.ViewProjectionMatrix);
		shader->SetMatrix4(m_SceneData.loc_Transform,   obj->GetTransform());
		shader->SetFloat(loc_numRows,					NumberOfRows);
		shader->SetVector2(loc_offset,					glm::vec2(  SMART_CAST(EntityMesh, obj)->GetTextureXOffset(), 
																	SMART_CAST(EntityMesh, obj)->GetTextureYOffset()));

		obj->Render();
	}
}