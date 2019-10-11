#pragma once

#include "Sprite.h"
#include "Glass/Layer.h"

class SceneLayer : public Glass::Layer
{
public:
	SceneLayer();
	~SceneLayer();

	void Update(float DeltaTime) override;
	void Render() override;
private:
	std::shared_ptr<Glass::Shader> shader;

	std::unique_ptr<Glass::OrthographicCamera> m_OrthographicCamera;
	std::shared_ptr<Mesh> m_Mesh;
};

