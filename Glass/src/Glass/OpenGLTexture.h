#pragma once

#include "Core.h"
#include "Texture.h"

namespace Glass
{
	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(const std::string& filename);
		OpenGLTexture(const std::string& filename, int numRows);
		virtual ~OpenGLTexture() { glDeleteTextures(1, &m_ID); }

		void SetNumberOfRows(int numRows) { m_NumberOfRows = numRows; }

		int& GetNumberOfRows() { return m_NumberOfRows; }
		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		int m_NumberOfRows;
		GLuint m_ID;
		uint32_t m_Width, m_Height;
		std::string m_Path;
	};
}



