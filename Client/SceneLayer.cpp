#include "SceneLayer.h"
#include "Glass/Renderer.h"
#include "Glass/Input.h"

std::vector<std::future<void>> m_Futures;
std::vector<Glass::Transform*> transforms;

SceneLayer::SceneLayer() 
{
	// layer sort index
	ZIndex = 0;

	// layer name
	SetName("gls_SceneLayer"); 

	// Init Camera
	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera>(0.0f, 1920.f, 1080.f, 0.0f);
	m_OrthographicCameraController = std::make_unique<OrthographicCameraController>();

	// Load in the shader and Add a Entity positioned within the center of the screen
	// Seperate Thread ------------
	m_Futures.push_back(std::async(std::launch::async, Glass::World::PushShader, std::make_shared<Glass::OpenGLShader>("Content/Shaders/basic.vs", "Content/Shaders/basic.fs"), "Basic"));
	m_Futures.push_back(std::async(std::launch::async, Glass::World::PushObject, std::make_shared<Glass::EntityMesh>(glm::vec3(100.0f, 100.0f, 0.f), 0)));
	// ----------------------------

	// Load in texture for object at index 0 in the ObjectList
	SMART_CAST(Glass::EntityMesh,		 Glass::World::GetObjectList()[0])->GetTexture() = Glass::Texture2D::Create("Content/DefaultAtlas.png");
	SMART_CAST(Glass::OpenGLTexture,	 std::dynamic_pointer_cast<Glass::EntityMesh>(Glass::World::GetObjectList()[0])->GetTexture())->SetNumberOfRows(2);

	// Animations
	std::vector<Glass::Frame> frames = { 3, 1, 2, 0 };
	m_Animation = std::make_shared<Glass::Animation>(std::dynamic_pointer_cast<Glass::EntityMesh>(Glass::World::GetObjectList()[0]), 
		glm::vec3(100.f, 100.f, 0.f), frames, 4, .2f);
	m_Animation->SetAnimationName("LeavesAnimation");

	// Push Textures into the tex library
	// Push Animations into the anim library
	Glass::TextureLibrary::Add("Default", SMART_CAST(Glass::EntityMesh, Glass::World::GetObjectList()[0])->GetTexture());
	Glass::AnimationLibrary::Add(m_Animation);

	// Initialise the renderer
	LayerRenderer.Init(Glass::World::GetShaderList()[0]);
}

SceneLayer::~SceneLayer()
{ 
	LayerRenderer.Destroy(); 
}

void SceneLayer::Update(float DeltaTime)
{
	m_OrthographicCameraController->SimulateControls(*m_OrthographicCamera, 0.5f, DeltaTime);

	Glass::AnimationLibrary::GetAnimationByName("LeavesAnimation")->Play(DeltaTime);
}

void SceneLayer::Render()
{
	LayerRenderer.Begin(*m_OrthographicCamera);
	{
		Glass::TextureLibrary::GetByName("Default")->Bind(0);
		LayerRenderer.Submit(Glass::World::GetObjectList()[0], Glass::World::GetShaderList()[0]);
	}
	LayerRenderer.End();
}
