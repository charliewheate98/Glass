#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Glass/Layer.h"

enum STYLES
{
	CLASSIC = 0,
	DARK,
	LIGHT
};

class ImGuiLayer : public Glass::Layer
{
public:
	ImGuiLayer(GLFWwindow* window, uint32_t style);
	~ImGuiLayer();

	void CreateFrame();

	void Update(float DeltaTime) override {}
	void Render() override;
private:
	ImVec4 clear_colour;
	uint32_t m_CurrentStyle = 0;
};

