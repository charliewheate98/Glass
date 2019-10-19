#include "MasterRenderer.h"
#include "Logger.h"

namespace Glass
{
	void MasterRenderer::Init(std::shared_ptr<Glass::OpenGLShader>& shader)
	{
		m_Shader = shader;

		m_Texture = Texture2D::Create("Content/Default.png");

		m_SceneData.loc_view = shader->LoadUniform("m_ViewProjection");
		m_SceneData.loc_Transform = shader->LoadUniform("m_Transform");
		m_SceneData.loc_Diffuse = shader->LoadUniform("m_Diffuse");
	}

	void MasterRenderer::ProcessMesh(std::shared_ptr<Mesh> obj, glm::mat4 transform)
	{
		if(!m_MeshRenderBuffer.empty())
			m_MeshRenderBuffer[obj].push_back(transform);
		else
		{
			std::vector<glm::mat4> newTransforms;
			newTransforms.push_back(transform);
			m_MeshRenderBuffer.insert({ obj, newTransforms });
		}
	}

	void MasterRenderer::Begin(OrthographicCamera& camera)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		m_SceneData.ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void MasterRenderer::Flush()
	{
		m_Shader->Bind();

		m_Shader->SetMatrix4(m_SceneData.loc_view, m_SceneData.ViewProjectionMatrix);

		for (std::map<std::shared_ptr<Mesh>, std::vector<glm::mat4>>::iterator it = m_MeshRenderBuffer.begin();
				it != m_MeshRenderBuffer.end(); ++it)
		{
			std::shared_ptr<Mesh> object = it->first;
			glm::mat4* transforms = &it->second[0];
			size_t numTransforms = it->second.size();

			if (numTransforms == 0)
				continue;

			m_Shader->SetInt(m_SceneData.loc_Diffuse, 0);
			m_Shader->SetMatrix4(m_SceneData.loc_Transform, transforms[it->second.size() - 1]);

			glBindVertexArray(object->GetVAO().GetVertexArray());
	
			m_Texture->Bind(0);

			glDrawElementsInstanced(GL_TRIANGLES, object->GetVertexCount(), GL_UNSIGNED_INT, 0, numTransforms);
		}
	}
}