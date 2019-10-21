#pragma once

#include "pch.h"
#include "Core.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Glass
{
	class GLASS_API VulkanContext
	{
	public:
		VulkanContext();
		~VulkanContext();

		void PrintContextInfo();
	private:
		uint32_t m_ExtensionCount;
	};
}



