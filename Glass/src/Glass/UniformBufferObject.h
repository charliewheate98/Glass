#pragma once

#include "Core.h"
#include "Buffer.h"

namespace Glass 
{
	struct UniformBufferElement 
	{
		void* m_Data;
		GLuint m_AlignmentOffset = 0;

		explicit UniformBufferElement(void * data, GLsizei size, GLuint offset) :
			m_Data(data),
			m_AlignmentOffset(offset)
		{
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
		}
		~UniformBufferElement() {}

		inline void* & GetData() { return m_Data; }
		constexpr GLuint & GetAlignmentOffset() { return m_AlignmentOffset; }
	};

	class GLASS_API UniformBufferObject : public Buffer
	{
	public:
		UniformBufferObject();
		~UniformBufferObject();

		void PushBlockElement(GLuint offset, GLsizei size, void * data);
		void UpdateBuffer(GLsizei buffer_size, void* buffer_data, GLenum usage);
		void BindBuffer() override;
	private:
		std::vector<UniformBufferElement> m_UniformBufferElement;
	};
}



