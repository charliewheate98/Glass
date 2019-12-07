#include "SceneLayer.h"
#include "Glass/Renderer.h"
#include "Glass/Input.h"
#include "Glass/BatchRenderer.h"
#include "Glass/DiffuseShader.h"

Glass::BatchRenderer m_BatchRenderer;
std::shared_ptr<Glass::OpenGLShader> m_QuadShader;
GLuint loc_fboTexture;

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
SceneLayer::SceneLayer() :
	Layer("gls_SceneLayer", 0)
{
	// Init Camera
	m_OrthographicCamera = std::make_unique<Glass::OrthographicCamera>(0.0f, 1920.f, 1080.f, 0.0f);
	m_OrthographicCameraController = std::make_unique<OrthographicCameraController>();

	// shaders
	std::shared_ptr<Glass::Shader> diffuseShader = std::make_shared<Glass::DiffuseShader>();
	m_QuadShader = std::make_shared<Glass::OpenGLShader>("Content/Shaders/Quad.vs", "Content/Shaders/Quad.fs");

	// fbos
	fbo = new Glass::FrameBufferObject({
			Glass::FrameBufferAttachment("Scene Colour Attachment", GL_COLOR_ATTACHMENT0, 1920, 1080, true)
		});

	// renderer
	m_BatchRenderer.Init(diffuseShader);
	m_BatchRenderer.Prepare(); 

	for (unsigned i = 0; i < 1000; ++i)
	{
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
	fbo->BindBuffer();
	m_BatchRenderer.Render(*m_OrthographicCamera);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_QuadShader->Bind();
	glUniform1i(m_QuadShader->LoadUniform("fboTexture"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbo->GetAttachments()[0].GetTexture());
	renderQuad();
}
