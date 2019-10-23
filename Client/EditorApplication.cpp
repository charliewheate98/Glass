#include "EditorApplication.h"
#include "SceneLayer.h"
#include "ImGuiLayer.h"
#include "Glass/Timestep.h"

void GetFramebufferSize(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

EditorApplication::EditorApplication(const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(GET_WINDOW_WIDTH, GET_WINDOW_HEIGHT, title, NULL, NULL);

	if (window == nullptr)
	{
		LOG_ERROR("Game Window Was Unable To Be Created!");
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, GetFramebufferSize);
	glfwSwapInterval(1); 

	GLContext = std::make_unique<Glass::OpenGLContext>();

	glViewport(0, 0, GET_WINDOW_WIDTH, GET_WINDOW_HEIGHT);

	m_SceneLayer = std::make_unique<SceneLayer>();
	m_GuiLayer = std::make_shared<ImGuiLayer>(window, CLASSIC);
}

EditorApplication::~EditorApplication() 
{
	m_DeltaTime = 0.f;
}

void EditorApplication::Tick(Glass::Timestep ts)
{
	m_SceneLayer->Update(ts);
}

void EditorApplication::Render()
{
	m_SceneLayer->Render();

	std::dynamic_pointer_cast<ImGuiLayer>(m_GuiLayer)->Render();
}

std::vector<std::string> menu_items;

void EditorApplication::MainLoop()
{
	float previousTime = (float)glfwGetTime();

	GLContext->PrintDeviceInfo();

	bool my_tool_active = true;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);

		std::dynamic_pointer_cast<ImGuiLayer>(m_GuiLayer)->CreateFrame();

		float currentTime = (float)glfwGetTime();
		Glass::Timestep timestep = currentTime - previousTime;
		previousTime = currentTime;

		Tick(timestep);
		Render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
