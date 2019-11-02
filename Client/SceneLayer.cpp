#include "SceneLayer.h"
#include "Glass/Renderer.h"
#include "Glass/Input.h"
#include "Glass/OpenALSource.h"
#include "Glass/BatchRenderer.h"

Glass::OpenALSource* alSound;

std::vector<std::future<void>> m_Futures;
std::vector<Glass::Transform*> transforms;

Glass::BatchRenderer m_BatchRenderer;

SceneLayer::SceneLayer() :
	Layer("gls_SceneLayer", 0)
{
	// Init Camera
	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera>(0.0f, 1920.f, 1080.f, 0.0f);
	m_OrthographicCameraController = std::make_unique<OrthographicCameraController>();

	alSound = new Glass::OpenALSource();

	// Load in the shader and Add a Entity positioned within the center of the screen
	// Seperate Thread ------------
	Glass::World::PushShader(std::make_shared<Glass::OpenGLShader>("Content/Shaders/basic.vs", "Content/Shaders/basic.fs"), "Basic");
	Glass::World::PushObject(std::make_shared<Glass::EntityMesh>(glm::vec3(100.0f, 100.0f, 0.f), 0));
	//for(unsigned int i = 0; i < 3; i++)
	// ----------------------------

	// Load in texture for object at index 0 in the ObjectList
	SMART_CAST(Glass::EntityMesh,		 Glass::World::GetObjectList()[0])->GetTexture() = Glass::Texture2D::Create("Content/DefaultAtlas.png");
	SMART_CAST(Glass::OpenGLTexture,	 std::dynamic_pointer_cast<Glass::EntityMesh>(Glass::World::GetObjectList()[0])->GetTexture())->SetNumberOfRows(2);

	// Animations
	std::vector<Glass::Frame> frames = { 0, 1, 2, 3 };
	m_Animation = std::make_shared<Glass::Animation>(std::dynamic_pointer_cast<Glass::EntityMesh>(Glass::World::GetObjectList()[0]), glm::vec3(100.f, 100.f, 0.f), frames, 4, .5f);
	m_Animation->SetAnimationName("LeavesAnimation");

	// Push Textures into the tex library
	// Push Animations into the anim library
	Glass::TextureLibrary::Add("Default",  SMART_CAST(Glass::EntityMesh, Glass::World::GetObjectList()[0])->GetTexture());
	Glass::AnimationLibrary::Add(m_Animation);

	// Initialise the renderer
	//LayerRenderer.Init(Glass::World::GetShaderList()[0]);
	
	// TEMP ///
	m_BatchRenderer.Init(Glass::World::GetShaderList()[0]);
	m_BatchRenderer.Prepare();

	for (unsigned int i = 0; i < 1000; i++)
	{
		for (unsigned int j = 0; j < 1000; j++)
		{
			m_BatchRenderer.SubmitData(glm::vec2(0.f + i * 0.8f, 0.f + j * 0.8f), glm::vec2(0.5f));
		}
	}

	m_BatchRenderer.UploadData();
	//
}

SceneLayer::~SceneLayer()
{ 
	LayerRenderer.Destroy(); 
}

void SceneLayer::Update(float DeltaTime)
{
	m_OrthographicCameraController->SimulateControls(*m_OrthographicCamera, 0.5f, DeltaTime);

	Glass::AnimationLibrary::GetAnimationByName("LeavesAnimation")->Play();
}

void SceneLayer::Render()
{
	//LayerRenderer.Begin(*m_OrthographicCamera);

	//Glass::TextureLibrary::GetByName("Default")->Bind(0);

	//for (unsigned int i = 0; i < Glass::World::GetObjectList().size(); i++)
	//	LayerRenderer.Submit(Glass::World::GetObjectList()[i], Glass::World::GetShaderList()[0]);
	//
	//LayerRenderer.End();


	// TEMP //
	m_BatchRenderer.Render(*m_OrthographicCamera);
	//
}
