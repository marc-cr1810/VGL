#pragma once

#include "VGL/Core.h"
#include "VGL/ExtensionList.h"
#include "VGL/Structures/ApplicationInfo.h"

#include <vector>

namespace VGL
{
	typedef struct VGLInstanceInfo
	{
	public:
		const void* Next;
		VGLApplicationInfo ApplicationInfo;
		ExtensionList Extensions;
		std::vector<const char*> EnabledLayers;

		static VGLInstanceInfo Create(VGLApplicationInfo appInfo);

		VkInstanceCreateInfo ToVkInstanceInfo();
	} InstanceInfo;
}

#define vglCreateInstanceInfo(appInfo) VGL::VGLInstanceInfo::Create(appInfo)