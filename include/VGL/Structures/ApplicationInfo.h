#pragma once

#include "VGL/Core.h"

namespace VGL
{
	typedef struct VGLApplicationInfo
	{
		const char* Name;
		uint32_t Version;
		const char* EngineName;
		uint32_t EngineVersion;
		uint32_t APIVersion;

		static VGLApplicationInfo Create(const char* name, uint32_t version);

		VkApplicationInfo ToVkApplicationInfo();
	} ApplicationInfo;
}

#define vglCreateApplicationInfo(name, version) VGL::ApplicationInfo::Create(name, version)
#define vglCreateVkApplicationInfo(name, version) VGL::ApplicationInfo::Create(name, version).ToVkApplicationInfo()