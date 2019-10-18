#pragma once

#include "Object.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Glass
{
	class GLASS_API Mesh : public Object
	{
	private:
		GLsizei m_VertexCount = 6;

		VertexArray* m_VertexArray;
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;

		SharedScope<Glass::Texture2D> m_Texture;
	public:
		Mesh(glm::vec3 position);
		~Mesh();

		VertexArray& GetVAO() { return *m_VertexArray; }
		inline GLsizei& GetVertexCount() { return m_VertexCount; }

		virtual void Tick(float DeltaTime) override;
		virtual void Render() override;
	};
}

