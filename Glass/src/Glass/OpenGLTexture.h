#pragma once

#include "Core.h"
#include "Texture.h"

namespace Glass
{
	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(const std::string& filename);
		virtual ~OpenGLTexture() { glDeleteTextures(1, &m_ID); }

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		GLuint m_ID;
		uint32_t m_Width, m_Height;
		std::string m_Path;
	};
}



