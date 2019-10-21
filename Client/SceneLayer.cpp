#include "SceneLayer.h"
#include "Glass/Renderer.h"
#include "Glass/Input.h"

std::vector<std::future<void>> m_Futures;

std::vector<Glass::Transform*> transforms;

SceneLayer::SceneLayer() 
{
	// layer sort index
	ZIndex = 0;

	SetName("gls_SceneLayer"); // layer name

	// Init Camera
	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera>(0.0f, 1920.f, 1080.f, 0.0f);
	m_OrthographicCameraController = std::make_unique<OrthographicCameraController>();

	m_Futures.push_back(std::async(std::launch::async, Glass::World::PushShader, std::make_shared<Glass::OpenGLShader>("Content/Shaders/basic.vs", "Content/Shaders/basic.fs"), "Basic"));
	m_Futures.push_back(std::async(std::launch::async, Glass::World::PushObject, std::make_shared<Glass::Mesh>(glm::vec3(1920.0f / 2, 1080.f / 2, 0.f))));

	// 50,000 sprites to test the InstanceRenderer 
	for (unsigned int i = 0; i < 1; i++)
	{	
		transforms.push_back(new Glass::Transform(glm::vec3(1920.f / 2 + i * 1024.f, 1080.f / 2, 0.0f), glm::vec3(512.f, 512.f, 0.0f)));
		transforms[i]->RecalculateTransformationMatrix();
	}

	// Initialise the renderer
	LayerRenderer.Init(Glass::World::GetShaderList()[0]);
	LayerRenderer.Process(Glass::World::GetObjectList()[0], transforms);
}

SceneLayer::~SceneLayer()
{ 
	LayerRenderer.Destroy(); 
}

void SceneLayer::Update(float DeltaTime)
{
	m_OrthographicCameraController->SimulateControls(*m_OrthographicCamera, 0.5f, DeltaTime);
}

void SceneLayer::Render()
{
	LayerRenderer.Begin(*m_OrthographicCamera);
	LayerRenderer.Submit(Glass::World::GetObjectList()[0], Glass::World::GetShaderList()[0]);
	LayerRenderer.End();
}
