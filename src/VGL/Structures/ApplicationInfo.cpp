#include "VGL/Structures/ApplicationInfo.h"

namespace VGL
{
	VGLApplicationInfo VGLApplicationInfo::Create(const char* name, uint32_t version)
	{
		VGLApplicationInfo appInfo{};
		appInfo.Name = name;
		appInfo.Version = version;
		appInfo.EngineName = "No Engine";
		appInfo.EngineVersion = VGL_VERSION_1_0;
		appInfo.APIVersion = VGL_API_VERSION_1_0;

		return appInfo;
	}

	VkApplicationInfo VGLApplicationInfo::ToVkApplicationInfo()
	{
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = Name;
		appInfo.applicationVersion = Version;
		appInfo.pEngineName = EngineName;
		appInfo.engineVersion = EngineVersion;
		appInfo.apiVersion = APIVersion;

		return appInfo;
	}
}