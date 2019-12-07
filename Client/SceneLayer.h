#pragma once

#include "Glass/EntityMesh.h"
#include "OrthographicCameraController.h"
#include "Glass/OpenGLShader.h"
#include "Glass/Layer.h"
#include "Glass/World.h"
#include "Glass/Animation.h"
#include "Glass/FrameBufferObject.h"

class SceneLayer : public Glass::Layer
{
public:
	SceneLayer();
	~SceneLayer();

	void Update(float DeltaTime) override;
	void Render() override;
private:
	Glass::FrameBufferObject* fbo;

	std::unique_ptr<Glass::OrthographicCamera> m_OrthographicCamera;
	std::unique_ptr<OrthographicCameraController> m_OrthographicCameraController;
	std::shared_ptr<Glass::Animation> m_Animation;
};

