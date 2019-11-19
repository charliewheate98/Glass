#include "SceneLayer.h"
#include "Glass/Renderer.h"
#include "Glass/Input.h"
#include "Glass/BatchRenderer.h"
#include "Glass/DiffuseShader.h"
#include "Glass/Text.h"

Glass::BatchRenderer m_BatchRenderer;

Glass::Text* text;

SceneLayer::SceneLayer() :
	Layer("gls_SceneLayer", 0)
{
	// Init Camera
	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera>(0.0f, 1920.f, 1080.f, 0.0f);
	m_OrthographicCameraController = std::make_unique<OrthographicCameraController>();

	// shaders
	std::shared_ptr<Glass::Shader> diffuseShader = std::make_shared<Glass::DiffuseShader>();
	m_TextShader = std::make_shared<Glass::TextShader>(); m_TextShader->LoadUniforms();
	//

	// textures 
	Glass::TextureLibrary::Add("BlueTile", Glass::Texture2D::Create("Content/Textures/Default.png", 1));


	text = new Glass::Text("Hello World", glm::vec2(1.f, 1.f));
	text->Process();

	// renderer
	m_BatchRenderer.Init(diffuseShader);
	m_BatchRenderer.Prepare(); 

	for (int i = 0; i < 10; i++) {
		m_BatchRenderer.SubmitData(glm::vec2(0.0f + i * 0.6f, 0.0f), glm::vec2(0.5f), glm::vec2(0.f), glm::vec2(1.f), glm::vec3(1.0f, 0.0f, 0.0f), 0);
	}
	
	m_BatchRenderer.UploadData();
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
	//Glass::TextureLibrary::GetByName("BlueTile")->Bind(0);
	//m_BatchRenderer.Render(*m_OrthographicCamera);

	m_TextShader->UseShader();

	glm::mat4 m = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f)) * glm::scale(glm::mat4(1.f), glm::vec3(256.f, 256.f, 0.f));

	m_TextShader->GetCoreShader()->SetMatrix4(m_TextShader->GetCoreShader()->LoadUniform("m_ViewProjection"), m_OrthographicCamera->GetViewProjectionMatrix());
	m_TextShader->GetCoreShader()->SetMatrix4(m_TextShader->GetCoreShader()->LoadUniform("m_Transform"), m);

	text->Render();
}
