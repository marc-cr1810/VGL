#pragma once

#include "VGL/Core.h"

#include "VGL/Structures/ApplicationInfo.h"
#include "VGL/Structures/InstanceInfo.h"

namespace VGL
{
	typedef struct VGLInstance
	{
		VGLInstanceInfo InstanceInfo;

		static VGLResult Create(VGLInstance* instance, VGLInstanceInfo info);

		void Destroy();
	private:
		VkInstance m_VkInstance;
	} Instance;
}

#define vglCreateInstance(instance, info) VGL::VGLInstance::Create(instance, info)

#define vglDestroyInstance(instance) instance.Destroy();