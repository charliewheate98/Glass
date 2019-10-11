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

#define GET_WINDOW_WIDTH 1920
#define GET_WINDOW_HEIGHT 1080
#define GLSL_VERSION "#version 440 core"

class EditorApplication : public Glass::Application
{
private:
	Glass::Layer* layer;
public:
	EditorApplication(const char* title);
	~EditorApplication();

	virtual void MainLoop()	           override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render()			   override;
};