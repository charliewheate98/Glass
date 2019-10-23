#include "Texture.h"
#include "OpenGLTexture.h"

namespace Glass
{
	std::unordered_map<std::string, SharedScope<Texture2D>> TextureLibrary::m_Textures;

	SharedScope<Texture2D> Texture2D::Create(const std::string& file)
	{
		return std::make_shared<OpenGLTexture>(file);
	}
}