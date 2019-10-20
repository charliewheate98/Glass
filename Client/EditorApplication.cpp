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
	glClearColor(0.01f, 0.01f, 0.01f, 1.f);

	m_SceneLayer = std::make_unique<SceneLayer>();
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
}

void EditorApplication::MainLoop()
{
	float previousTime = (float)glfwGetTime();

	int frames = 0;

	GLContext->PrintDeviceInfo();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		float currentTime = (float)glfwGetTime();
		Glass::Timestep timestep = currentTime - previousTime;
		previousTime = currentTime;

		#ifdef _DEBUG
				LOG_TRACE("MS: {0}", timestep.GetMilliseconds());
				LOG_TRACE("SC: {0}", timestep.GetSeconds());
		#endif

		Tick(timestep);
		Render();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
