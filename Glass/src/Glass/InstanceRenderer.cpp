#include "InstanceRenderer.h"
#include "OpenGLTexture.h"

namespace Glass
{
	SharedScope<Texture2D> m_Texture;

	void InstanceRenderer::Init(std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		m_Shader = shader;

		RendererCommands::Init();

		m_Texture = Glass::Texture2D::Create("Content/Default.png");

		m_SceneData.loc_view = m_Shader->LoadUniform("m_ViewProjection");
		m_SceneData.loc_Transform = m_Shader->LoadUniform("m_Transform");
		m_SceneData.loc_Diffuse = m_Shader->LoadUniform("m_Diffuse");
	}

	void InstanceRenderer::Process(const std::shared_ptr<Object>& obj, std::vector<Glass::Transform*> transforms)
	{
		for (unsigned int i = 0; i < transforms.size(); i++)
			m_Transforms.push_back(transforms[i]->GetCoreMatrix());

		VertexBuffer m_Buffer(transforms.size() * sizeof(glm::mat4), &m_Transforms[0], GL_STATIC_DRAW);

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
		shader->Bind();

		shader->SetInt(m_SceneData.loc_Diffuse, 0);
		shader->SetMatrix4(m_SceneData.loc_view, m_SceneData.ViewProjectionMatrix);

		m_Texture->Bind(0);

		RendererCommands::DrawIndexed(std::dynamic_pointer_cast<Mesh>(obj)->GetVAO(), 6, m_Transforms.size());
	}

	void InstanceRenderer::Destroy()
	{
		m_Transforms.clear();
	}
}