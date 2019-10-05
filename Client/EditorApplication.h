#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "Glass/Glass.h"

#define GET_WINDOW_WIDTH 1920
#define GET_WINDOW_HEIGHT 1080

class EditorApplication : public Glass::Application
{
private:
	GLFWwindow* window;
public:
	EditorApplication(const char* title);
	~EditorApplication();

	void MainLoop() override;
	void Tick(float DeltaTime) override;
	void Render() override;
};

