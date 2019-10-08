#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "Glass/Shader.h"
#include "Glass/Glass.h"

#define GET_WINDOW_WIDTH 1920
#define GET_WINDOW_HEIGHT 1080
#define GLSL_VERSION "#version 440 core"

class EditorApplication : public Glass::Application
{
private:	
	std::vector<std::shared_ptr<Glass::Shader>> shaders;
public:
	EditorApplication(const char* title);
	~EditorApplication();

	virtual void MainLoop()			   override;
	virtual void Tick(float DeltaTime) override;
	virtual void Render()			   override;
};

