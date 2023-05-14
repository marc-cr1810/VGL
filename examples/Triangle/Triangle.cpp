#define VK_USE_PLATFORM_WIN32_KHR
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "VGL/vgl.h"

#include <iostream>

using namespace VGL;

class TriangleApplication
{
public:
	void Run()
	{
        InitWindow();
        InitVulkan();
        MainLoop();
        Cleanup();
	}
private:
    void InitWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        m_Window = glfwCreateWindow(m_Width, m_Height, "Vulkan Triangle", nullptr, nullptr);
    }

    void InitVulkan()
    {
        ApplicationInfo appInfo = vglCreateApplicationInfo("Triangle", VGL_VERSION_1_0);

        InstanceInfo createInfo = vglCreateInstanceInfo(appInfo);
        ExtensionList extensions;
        extensions.AddList(GetRequiredExtensions());

        createInfo.Extensions = extensions;

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (m_EnableValidationLayers)
        {
            PopulateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.Next = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }

        if (vglCreateInstance(&m_Instance, createInfo) != VGL_RESULT_SUCCESS)
            throw std::runtime_error("Failed to create VGL instance!");
    }

    std::vector<VGLExtension> GetRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        VGLExtension* glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<VGLExtension> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (m_EnableValidationLayers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
    }


    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = DebugCallback;
    }

    void MainLoop()
    {
        while (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();
        }
    }

    void Cleanup()
    {
        vglDestroyInstance(m_Instance);

        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
private:
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }
private:
    Instance m_Instance;

    GLFWwindow* m_Window = nullptr;

    const uint32_t m_Width = 800;
    const uint32_t m_Height = 600;

#if VGL_DEBUG
    const bool m_EnableValidationLayers = true;
#else
    const bool m_EnableValidationLayers = false;
#endif
};

int main()
{
	TriangleApplication app;

    try
    {
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}