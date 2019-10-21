#include "World.h"

namespace Glass
{
	std::mutex World::m_Mutex;
	std::queue<std::shared_ptr<Glass::OpenGLShader>> World::m_Shaders;
}