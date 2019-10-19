#include "SceneLayer.h"
#include "Glass/Renderer.h"
#include "Glass/Input.h"

std::vector<glm::mat4> transforms;

SceneLayer::SceneLayer() 
{
	// layer sort index
	ZIndex = 0;

	SetName("gls_SceneLayer"); // layer name

	// Init Camera
	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera>(0.0f, 1920.f, 1080.f, 0.0f);
	m_OrthographicCameraController = std::make_unique<OrthographicCameraController>();

	// Init Shader
	shader = std::make_shared<Glass::OpenGLShader>("Content/Shaders/basic.vs", "Content/Shaders/basic.fs");
	shader->SetShaderName("Basic"); // give this shader a name for access from the shader library
	Glass::ShaderLibrary::Add(shader); // push this into the shader library

	m_Meshes.push_back(std::make_shared<Glass::Mesh>(glm::vec3(1920.0f / 2, 1080.f / 2, 0.f)));
	
	// Render 50,000 sprites to test the InstanceRenderer 
	for (unsigned int i = 0; i < 50000; i++)
	{	
		transforms.push_back(glm::translate(glm::mat4(1.f), glm::vec3(1920.f / 2 + i * 512.f, 1080.f / 2, 0.0f)) *
						     glm::scale(glm::mat4(1.f), glm::vec3(128.f, 128.f, 0.0f)));
	}

	// Initialise the renderer
	LayerRenderer.Init(shader);
	LayerRenderer.Process(m_Meshes[0], transforms);
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
	LayerRenderer.Submit(m_Meshes[0], shader);
	LayerRenderer.End();
}
