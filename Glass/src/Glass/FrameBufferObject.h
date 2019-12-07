#pragma once

#include "FrameBufferAttachment.h"

namespace Glass
{
	#define MAX_SUPPORTED_ATTACHMENTS 0x8

	class GLASS_API FrameBufferObject : public Buffer
	{
	public:
		FrameBufferObject(std::vector<FrameBufferAttachment> attachments);
		~FrameBufferObject();

		inline std::vector<FrameBufferAttachment> & GetAttachments() { return _attachments; }

		void BindBuffer() override;
	private:
		unsigned						   _fbo;
		std::vector<FrameBufferAttachment> _attachments;
	};
}



