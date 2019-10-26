#pragma once

#include "Glass/Mesh.h"
#include "OrthographicCameraController.h"
#include "Glass/OpenGLShader.h"
#include "Glass/Layer.h"
#include "Glass/World.h"
#include "Glass/Animation.h"

class SceneLayer : public Glass::Layer
{
public:
	SceneLayer();
	~SceneLayer();

	void Update(float DeltaTime) override;
	void Render() override;
private:
	std::unique_ptr<Glass::OrthographicCamera> m_OrthographicCamera;
	std::unique_ptr<OrthographicCameraController> m_OrthographicCameraController;

	Glass::Animation* m_Animation;

	std::vector<std::shared_ptr<Glass::Mesh>> m_Meshes;
};

