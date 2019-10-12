#include "SceneLayer.h"
#include "Glass/Renderer.h"
#include "Glass/Input.h"

SceneLayer::SceneLayer() 
{
	ZIndex = 0;

	SetName("gls_SceneLayer");

	m_Mesh = std::make_shared<Mesh>();

	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera>(0.0f, 800.0f, 600.0f, 0.0f);
	m_OrthographicCameraController = std::make_unique<OrthographicCameraController>();

	shader = std::make_shared<Glass::Shader>("Content/Shaders/basic.vs", "Content/Shaders/basic.fs");
	shader->SetShaderName("Basic");

	Glass::Renderer::Init(shader);

	Glass::ShaderLibrary::Add(shader);
}

SceneLayer::~SceneLayer(){}

void SceneLayer::Update(float DeltaTime)
{
	m_OrthographicCameraController->SimulateControls(*m_OrthographicCamera, 0.5f, DeltaTime);
}

void SceneLayer::Render()
{
	Glass::Renderer::BeginScene(*m_OrthographicCamera);

	Glass::Renderer::Submit(m_Mesh, shader, glm::translate(glm::mat4(1.f), glm::vec3(100.0f, 100.0f, 0.0f)) *
											glm::scale(glm::mat4(1.f), glm::vec3(512.f, 512.f, 0.f)));

	Glass::Renderer::EndScene();
}
