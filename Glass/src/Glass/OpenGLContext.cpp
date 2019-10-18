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
	}

	void OpenGLContext::PrintDeviceInfo()
	{
		LOG_INFO(glGetString(GL_VERSION));
		LOG_INFO(glGetString(GL_RENDERER));
		LOG_INFO(glGetString(GL_VENDOR));
	}
}