#include "FrameBufferObject.h"
#include "Logger.h"

namespace Glass
{
	FrameBufferObject::FrameBufferObject(std::vector<FrameBufferAttachment> fbo_attachments)
	{
		_attachments = fbo_attachments;

		glGenFramebuffers(1, &_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

		_attachments.reserve(MAX_SUPPORTED_ATTACHMENTS);

		for (size_t i = 0; i < _attachments.size(); ++i)
			_attachments[i].Create();

		if (_attachments.size() == NULL)
			LOG_WARN("No Attachments in Fbo");
	}

	FrameBufferObject::~FrameBufferObject()
	{
		glDeleteFramebuffers(1, &_fbo);
	}

	void FrameBufferObject::BindBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
