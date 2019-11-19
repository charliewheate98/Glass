#include "ImGuiLayer.h"
#include "Glass/World.h"

ImGuiLayer::ImGuiLayer(GLFWwindow* window, uint32_t style) : 
	Layer("gls_EditorGuiLayer", 0)
{
	if (window != nullptr)
	{
		clear_colour = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		if (style == CLASSIC)
			ImGui::StyleColorsClassic();
		else if (style == DARK)
			ImGui::StyleColorsDark();
		else if (style == LIGHT)
			ImGui::StyleColorsLight();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 440 core");
	}
	else
		LOG_ERROR("ImGui Failed to be initialised as the window is NULL!");
}

ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::CreateFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Outliner");
	ImGui::Text("Tools");
	ImGui::Separator();
	if (ImGui::Button("Instantiate Static Sprite")) {}
	if (ImGui::Button("Instantiate Animated Sprite")) {}
	ImGui::Separator();
	ImGui::End();

	// World Inspector Window
	ImGui::Begin("Home Inspector");
	ImGui::Text("Background Settings");
	ImGui::Separator();
	ImGui::ColorEdit3("Colour", (float*)&clear_colour);
	ImGui::Separator();

	ImGui::Text("IO Settings");
	ImGui::Separator();
	if(ImGui::Button("Load Map")) {}
	if(ImGui::Button("Save Map")) {}
	ImGui::Separator();
	ImGui::End();
}

void ImGuiLayer::Render()
{
	glClearColor(clear_colour.x, clear_colour.y, clear_colour.z, 1.f);

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(1920.0f, 1080.0f);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

}

