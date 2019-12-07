#pragma once

#include "Buffer.h"

namespace Glass
{
	class GLASS_API VertexBuffer : public Buffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void UpdateBuffer(GLsizei buffer_size, void* buffer_data, GLenum usage);
		void BindBuffer() override;
	};
}



