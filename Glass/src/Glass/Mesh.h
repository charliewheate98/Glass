#pragma once

#include "Object.h"
#include "Texture.h"
#include "OpenGLTexture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Glass
{
	class GLASS_API Mesh : public Object
	{
	private:
		VertexArray* m_VertexArray;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;

		int m_TextureIndex;

		GLsizei m_VertexCount = { 0 };
	protected:
		SharedScope<Texture2D> m_Texture;
	public:
		Mesh(glm::vec3 position, int texture_index = 0);
		~Mesh();

		SharedScope<Texture2D>& GetTexture() { return m_Texture; }
		VertexArray& GetVAO() { return *m_VertexArray; }
		VertexBuffer& GetVBO() { return *m_VertexBuffer; }
		GLsizei& GetVertexCount() { return m_VertexCount; }
		int& GetTextureIndex() { return m_TextureIndex; }

		float GetTextureXOffset()
		{
			int column = GetTextureIndex() % std::dynamic_pointer_cast<OpenGLTexture>(m_Texture)->GetNumberOfRows();
			return static_cast<float>(column) / static_cast<float>(std::dynamic_pointer_cast<OpenGLTexture>(m_Texture)->GetNumberOfRows());
		}

		float GetTextureYOffset()
		{
			int row = (int)glm::floor(GetTextureIndex() / std::dynamic_pointer_cast<OpenGLTexture>(m_Texture)->GetNumberOfRows());
			return (float)row / (float)std::dynamic_pointer_cast<OpenGLTexture>(m_Texture)->GetNumberOfRows();
		}

		virtual void Tick(float DeltaTime) override;
		virtual void Render() override;
	};
}

