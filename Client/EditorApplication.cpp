#include "EditorApplication.h"

void GetFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

EditorApplication::EditorApplication(const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(GET_WINDOW_WIDTH, GET_WINDOW_HEIGHT, title, NULL, NULL);

	if (window == nullptr)
	{
		LOG_ERROR("Game Window Was Unable To Be Created!");
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, GetFramebufferSize);

	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK)
	{
		LOG_ERROR("Unable To Initialise Glew!");
		return;
	}

	glViewport(0, 0, GET_WINDOW_WIDTH, GET_WINDOW_HEIGHT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 440 core");
}

EditorApplication::~EditorApplication()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void EditorApplication::Tick(float DeltaTime) {}
void EditorApplication::Render()
{
	{
		ImGui::Begin("Global Properties");
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorApplication::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Tick(0.f);
		Render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}
