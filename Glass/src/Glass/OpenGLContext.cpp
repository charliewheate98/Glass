#include "OpenGLContext.h"
#include "Logger.h"

namespace Glass
{
	OpenGLContext::OpenGLContext()
	{
		GLenum glewStatus = glewInit();
		
		if (glewStatus != GLEW_OK)
		{
			LOG_ERROR("Unable To Initialise Glew!");
			return;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glViewport(0, 0, 1920, 1080);
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	}

	void OpenGLContext::PrintDeviceInfo()
	{
		LOG_INFO(glGetString(GL_VERSION));
		LOG_INFO(glGetString(GL_RENDERER));
		LOG_INFO(glGetString(GL_VENDOR));
	}
}