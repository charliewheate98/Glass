#include "InstanceRenderer.h"
#include "EntityMesh.h"
#include "OpenGLTexture.h"

namespace Glass
{
	GLuint loc_inumRows;
	GLuint loc_ioffset;

	void InstanceRenderer::Init(std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		m_Shader = shader;

		RendererCommands::Init();

		m_SceneData.loc_view = m_Shader->LoadUniform("m_ViewProjection");
		m_SceneData.loc_Transform = m_Shader->LoadUniform("m_Transform");
		m_SceneData.loc_Diffuse = m_Shader->LoadUniform("m_Diffuse");

		loc_inumRows = m_Shader->LoadUniform("m_NumberOfRows");
		loc_ioffset = m_Shader->LoadUniform("m_Offset");
	}

	void InstanceRenderer::Process(const std::shared_ptr<Object>& obj, std::vector<Glass::Transform*> transforms)
	{
		for (unsigned int i = 0; i < transforms.size(); i++)
			m_Transforms.push_back(transforms[i]->GetCoreMatrix());

		VertexBuffer m_Buffer();

		std::dynamic_pointer_cast<Mesh>(obj)->GetVAO().BindVertexArray();

		// set up the matrix 4 attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));

		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);

		glBindVertexArray(0);
	}

	void InstanceRenderer::Begin(OrthographicCamera& camera)
	{
		RendererCommands::Clear();

		m_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void InstanceRenderer::End() 
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void InstanceRenderer::Submit(const std::shared_ptr<Object>& obj, const std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		static auto& NumberOfRows  = SMART_CAST(OpenGLTexture, std::dynamic_pointer_cast<EntityMesh>(obj)->GetTexture())->GetNumberOfRows();
		static auto  xOffset       = SMART_CAST(EntityMesh, obj)->GetTextureXOffset();
		static auto  yOffset       = SMART_CAST(EntityMesh, obj)->GetTextureYOffset();

		shader->Bind();

		shader->SetInt      (m_SceneData.loc_Diffuse,    0);
		shader->SetMatrix4  (m_SceneData.loc_view,       m_SceneData.ViewProjectionMatrix);
		shader->SetFloat    (loc_inumRows,               STATIC_CAST(float, NumberOfRows));
		shader->SetVector2  (loc_ioffset,		         glm::vec2(xOffset, yOffset));

		RendererCommands::DrawIndexedInst(std::dynamic_pointer_cast<EntityMesh>(obj)->GetVAO(), 6, (GLsizei)m_Transforms.size());
	}

	void InstanceRenderer::Destroy()
	{
		m_Transforms.clear();
	}
}