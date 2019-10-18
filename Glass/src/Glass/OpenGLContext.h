#pragma once

#include "pch.h"
#include "Core.h"

namespace Glass
{
	class GLASS_API OpenGLContext
	{
	public:
		OpenGLContext();
		~OpenGLContext() = default;

		void PrintDeviceInfo();
	};
}



