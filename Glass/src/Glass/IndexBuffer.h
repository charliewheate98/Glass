#pragma once

#include "Buffer.h"

namespace Glass
{
	class GLASS_API IndexBuffer : public Buffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void UpdateBuffer(GLsizei buffer_size, void* buffer_data, GLenum usage);
		void BindBuffer() override;
	};
}



