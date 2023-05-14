#include "VGL/Structures/InstanceInfo.h"

namespace VGL
{
	VGLInstanceInfo VGLInstanceInfo::Create(VGLApplicationInfo appInfo)
	{
		VGLInstanceInfo createInfo{};
		createInfo.ApplicationInfo = appInfo;
		createInfo.Next = nullptr;

		return createInfo;
	}

	VkInstanceCreateInfo VGLInstanceInfo::ToVkInstanceInfo()
	{
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &ApplicationInfo.ToVkApplicationInfo();
		createInfo.pNext = Next;

		createInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.Size());
		if (Extensions.Size() > 0)
			createInfo.ppEnabledExtensionNames = Extensions.Data();

		createInfo.enabledLayerCount = static_cast<uint32_t>(EnabledLayers.size());
		if (EnabledLayers.size() > 0)
			createInfo.ppEnabledLayerNames = EnabledLayers.data();

		return createInfo;
	}
}