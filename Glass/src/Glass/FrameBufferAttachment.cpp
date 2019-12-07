#include "FrameBufferAttachment.h"
#include "Logger.h"

namespace Glass
{
	FrameBufferAttachment::FrameBufferAttachment(const char* name,
												 const GLenum attachment_type,
												 GLsizei src_width,
												 GLsizei src_height,
												 const bool compressed) :
		_attachment_buffer(NULL),
		_attachment_type(attachment_type),
		_width(src_width),
		_height(src_height),
		_name(name),
		_iscompressed(compressed)
	{}

	bool FrameBufferAttachment::Create()
	{
		glGenTextures(1, &_attachment_buffer);
		glBindTexture(GL_TEXTURE_2D, _attachment_buffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, _attachment_type, GL_TEXTURE_2D, _attachment_buffer, NULL);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ERROR("Error : FBO Could not be created!"); 
			return false;
		}

#ifdef _DEBUG
		GLint maxAttach = 0;
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
		LOG_TRACE(maxAttach + " Colour Attachments are Supported");
#endif

		return true;
	}

	FrameBufferAttachment::~FrameBufferAttachment()
	{
		glDeleteTextures(1, &_attachment_buffer);
	}
}
