#pragma once

// Lib Classes
#include <GL/glew.h>

// Editor Classes
#include "Sprite.h"

// Engine Classes
#include "Glass/Input.h"
#include "Glass/Shader.h"
#include "Glass/Glass.h"
#include "Glass/Layer.h"

#define GET_WINDOW_WIDTH 800
#define GET_WINDOW_HEIGHT 600
#define GLSL_VERSION "#version 440 core"

class EditorApplication : public Glass::Application
{
private:
	std::shared_ptr<Glass::Layer> m_SceneLayer;

	float m_DeltaTime;
public:
	EditorApplication(const char* title);
	~EditorApplication();

	virtual void MainLoop()	           override;
	virtual void Tick() override;
	virtual void Render()			   override;
};