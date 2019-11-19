#include "Texture.h"
#include "OpenGLTexture.h"
#include "World.h"

namespace Glass
{
	std::unordered_map<std::string, SharedScope<Texture2D>> TextureLibrary::m_Textures;
	GLuint Texture2D::loc_NumRows;

	SharedScope<Texture2D> Texture2D::Create(const std::string& file, int num_rows)
	{
		return std::make_shared<OpenGLTexture>(file);
	}
}