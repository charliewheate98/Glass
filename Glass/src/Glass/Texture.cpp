#include "Texture.h"
#include "OpenGLTexture.h"

namespace Glass
{
	SharedScope<Texture2D> Texture2D::Create(const std::string& file)
	{
		return std::make_shared<OpenGLTexture>(file);
	}
}