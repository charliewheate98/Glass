#include "SceneLayer.h"
#include "Glass/Renderer.h"
#include "Glass/Input.h"

SceneLayer::SceneLayer() 
{
	ZIndex = 0;

	SetName("gls_SceneLayer");

	m_Meshes.push_back(std::make_shared<Glass::Mesh>(glm::vec3(400.f, 300.f, 0.f)));
	m_Meshes.push_back(std::make_shared<Glass::Mesh>(glm::vec3(100.f, 100.f, 0.f)));

	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera>(0.0f, 1920.f, 1080.f, 0.0f);
	m_OrthographicCameraController = std::make_unique<OrthographicCameraController>();

	shader = std::make_shared<Glass::OpenGLShader>("Content/Shaders/basic.vs", "Content/Shaders/basic.fs");
	shader->SetShaderName("Basic");

	LayerRenderer.Init();

	Glass::ShaderLibrary::Add(shader);
}

SceneLayer::~SceneLayer(){}

void SceneLayer::Update(float DeltaTime)
{
	m_OrthographicCameraController->SimulateControls(*m_OrthographicCamera, 0.5f, DeltaTime);
}

void SceneLayer::Render()
{
	//glClear(GL_COLOR_BUFFER_BIT);

	//LayerRenderer.Begin(*m_OrthographicCamera);

	//LayerRenderer.Submit(m_Meshes[0], shader);
	//
	//LayerRenderer.End();
}
