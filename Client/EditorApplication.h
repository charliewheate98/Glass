#pragma once

// Lib Classes
#include <GL/glew.h>

// Editor Classes
#include "Glass/Mesh.h"

// Engine Classes
#include "Glass/Input.h"
#include "Glass/Glass.h"
#include "Glass/Layer.h"
#include "Glass/OpenGLContext.h"

#define GET_WINDOW_WIDTH 1920
#define GET_WINDOW_HEIGHT 1080
#define GLSL_VERSION "#version 440 core"

class EditorApplication : public Glass::Application
{
private:
	std::unique_ptr<Glass::Layer> m_SceneLayer;
	std::unique_ptr<Glass::OpenGLContext> GLContext;

	float m_DeltaTime;
public:
	EditorApplication(const char* title);
	~EditorApplication();

	virtual void MainLoop()	           override;
	virtual void Tick(Glass::Timestep ts)	   override;
	virtual void Render()			   override;
};