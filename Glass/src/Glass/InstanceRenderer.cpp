#include "InstanceRenderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

unsigned int instanceBuffer;

namespace Glass
{
	void InstanceRenderer::Init(std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		m_Shader = shader;

		RendererCommands::Init();

		m_SceneData.loc_view = m_Shader->LoadUniform("m_ViewProjection");
		m_SceneData.loc_Transform = m_Shader->LoadUniform("m_Transform");
	}

	void InstanceRenderer::Process(const std::shared_ptr<Object>& obj, std::vector<glm::mat4> &transforms) 
	{
		m_Transforms = transforms;

		VertexBuffer m_Buffer(transforms.size() * sizeof(glm::mat4), &transforms[0], GL_STATIC_DRAW);

		std::dynamic_pointer_cast<Mesh>(obj)->GetVAO().BindVertexArray();

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

		shader->SetMatrix4(m_SceneData.loc_view, m_SceneData.ViewProjectionMatrix);

		RendererCommands::DrawIndexed(std::dynamic_pointer_cast<Mesh>(obj)->GetVAO(), 6, m_Transforms.size());
	}

	void InstanceRenderer::Destroy()
	{
		m_Transforms.clear();

	}
}