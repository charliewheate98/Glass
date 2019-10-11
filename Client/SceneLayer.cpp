#include "SceneLayer.h"
#include "Glass/Renderer.h"

extern std::vector<std::shared_ptr<Glass::Shader>> shaders;

SceneLayer::SceneLayer() 
{
	SetName("gls_SceneLayer");

	m_Mesh = std::make_shared<Mesh>();

	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera> (0.0f, 1920.0f, 1080.0f, 0.0f);

	shader = std::make_shared<Glass::Shader>("Content/Shaders/basic.vs", "Content/Shaders/basic.fs");
}

SceneLayer::~SceneLayer()
{
}

void SceneLayer::Update(float DeltaTime)
{
}

void SceneLayer::Render()
{
	Glass::Renderer::BeginScene(*m_OrthographicCamera);

	Glass::Renderer::Submit(m_Mesh, shader, glm::translate(glm::mat4(1.f), glm::vec3(100.0f, 100.0f, 0.0f)) *
											glm::scale(glm::mat4(1.f), glm::vec3(128.f, 128.f, 0.f)));

	Glass::Renderer::EndScene();
}
