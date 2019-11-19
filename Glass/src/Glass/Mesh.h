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
		// This meshes index on the atlas
		int m_TextureIndex;

		// Buffers
		VertexArray* m_VertexArray;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;

		// Amount of vertices on this mesh
		GLsizei m_VertexCount = 0;
	protected:
		// This Meshes Texture
		SharedScope<Texture2D> m_Texture;
	public:
		// Default Constructer
		Mesh() = default;

		// Constructer
		Mesh(glm::vec3 position, int texture_index = 0);

		// Destructer
		~Mesh();

		// set the texture index of this mesh
		void SetTextureIndex(int val) { m_TextureIndex = val; }

		SharedScope<Texture2D>& GetTexture() { return m_Texture; }
		VertexArray& GetVAO() { return *m_VertexArray; }
		VertexBuffer& GetVBO() { return *m_VertexBuffer; }
		GLsizei& GetVertexCount() { return m_VertexCount; }
		int& GetTextureIndex() { return m_TextureIndex; }

		float GetTextureXOffset()
		{
			int column = GetTextureIndex() % std::dynamic_pointer_cast<OpenGLTexture>(m_Texture)->GetNumberOfRows();
			return (float)column / (float)std::dynamic_pointer_cast<OpenGLTexture>(m_Texture)->GetNumberOfRows();
		}

		float GetTextureYOffset()
		{
			int row = GetTextureIndex() / std::dynamic_pointer_cast<OpenGLTexture>(m_Texture)->GetNumberOfRows();
			return (float)row / (float)std::dynamic_pointer_cast<OpenGLTexture>(m_Texture)->GetNumberOfRows();
		}

		virtual void Tick(float DeltaTime) override;
		virtual void Render() override;
	};
}

