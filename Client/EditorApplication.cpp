#include "EditorApplication.h"
#include "SceneLayer.h"
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

	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK)
	{
		LOG_ERROR("Unable To Initialise Glew!");
		return;
	}

	GLContext = std::make_unique<Glass::OpenGLContext>();

	glViewport(0, 0, GET_WINDOW_WIDTH, GET_WINDOW_HEIGHT);
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);

	//ImGui::CreateContext();
	//ImGui::StyleColorsDark();
	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	//ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	m_SceneLayer = std::make_shared<SceneLayer>();
}

EditorApplication::~EditorApplication() {}

void EditorApplication::Tick(Glass::Timestep ts)
{
	m_SceneLayer->Update(ts);
}

void EditorApplication::Render()
{
	m_SceneLayer->Render();

	//ImGui::Render();
	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorApplication::MainLoop()
{
	float previousTime = (float)glfwGetTime();

	GLContext->PrintDeviceInfo();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		float currentTime = (float)glfwGetTime();
		Glass::Timestep timestep = currentTime - previousTime;
		previousTime = currentTime;

		// Start the ImGui frame
		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();

		//ImGui::Begin("Transform");
		//ImGui::End();

		#ifdef _DEBUG
				LOG_INFO("Seconds: {0}", timestep.GetSeconds());
				LOG_INFO("Milliseconds: {0}", timestep.GetMilliseconds());
		#endif

		Tick(timestep);
		Render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Cleanup
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}
