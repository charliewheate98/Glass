#pragma once

#include "Application.h"
#include "Buffer.h"

namespace Glass
{
	class GLASS_API FrameBufferAttachment
	{
	public:
		FrameBufferAttachment(const char* name, 
							  const GLenum attachment_type, 
							  GLsizei src_width, 
  							  GLsizei src_height,
							  const bool compressed = false);
		~FrameBufferAttachment();

		bool Create();

		inline const char* & GetAttachmentName()                    { return _name;				 }
		inline const unsigned & GetTexture() const		            { return _attachment_buffer; }
		inline const GLenum & GetAttachmentType() const				{ return _attachment_type;   }
		inline GLsizei & GetWidth()									{ return _width;			 }
		inline GLsizei & GetHeight()								{ return _height;            }
	private:
		bool		_iscompressed;
		const char* _name;
		unsigned	_attachment_buffer;
		GLenum		_attachment_type;
		GLsizei		_width;
		GLsizei		_height;
	};
}



