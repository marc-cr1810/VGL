#include "VGL/Instance.h"

namespace VGL
{
	VGLResult VGLInstance::Create(VGLInstance* instance, VGLInstanceInfo info)
	{
		instance->InstanceInfo = info;

		return vglToVGLResult(vkCreateInstance(&info.ToVkInstanceInfo(), nullptr, &instance->m_VkInstance));
	}

	void VGLInstance::Destroy()
	{
		vkDestroyInstance(m_VkInstance, nullptr);
	}
}