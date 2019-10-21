#include "VulkanContext.h"
#include "Logger.h"

#include <vulkan/vulkan.h>

namespace Glass
{
	VulkanContext::VulkanContext() : 
		m_ExtensionCount(0)
	{
		vkEnumerateInstanceExtensionProperties(nullptr, &m_ExtensionCount, nullptr);

		LOG_INFO("Extensions Supported: {0}", m_ExtensionCount);
	}

	VulkanContext::~VulkanContext()
	{
		m_ExtensionCount = NULL;
	}

	void VulkanContext::PrintContextInfo()
	{
		
	}
}