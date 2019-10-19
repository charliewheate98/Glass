#pragma once

#include "Renderer.h"

namespace Glass
{
	class GLASS_API InstanceRenderer : public Renderer
	{
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;

			GLuint loc_view;
			GLuint loc_Transform;
		};
		SceneData m_SceneData;

		std::vector<glm::mat4> m_Transforms;
		std::shared_ptr<Glass::OpenGLShader> m_Shader;
	public:
		void Process(const std::shared_ptr<Object>& obj, std::vector<glm::mat4> &transforms);

		void Init(std::shared_ptr<Glass::OpenGLShader>& shader)												    override;
		void Begin(OrthographicCamera& camera)																    override;
		void End()																								override;
		void Submit(const std::shared_ptr<Object>& obj, const std::shared_ptr<Glass::OpenGLShader>& shader)		override;
		void Destroy()																							override;
	};
}



