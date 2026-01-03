#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

#define VK_NO_PROTOTYPES
#include <volk/volk.h>
#undef VK_NO_PROTOTYPES

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
// import vulkan;  // Needs a working LLVM toolchain (this is Bazel's fault, not MSVC's)

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "ui.hpp"

#ifdef NDEBUG
constexpr bool ndebug = true;
#else
constexpr bool ndebug = false;
#endif

const std::vector<char const*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

bool init() {
    if (!glfwInit()) { return false; }
    if (!glfwVulkanSupported()) { return false; }
    if (volkInitialize() != VK_SUCCESS) { return false; }
    return true;
}

void cleanup() {
    glfwTerminate();
}

class Window {
    GLFWwindow* window = nullptr;
    vk::raii::Context context;
    vk::raii::Instance instance = nullptr;
    constexpr static int WIDTH = 800;
    constexpr static int HEIGHT = 600;

public:
    Window() {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        
        constexpr vk::ApplicationInfo appInfo{
            .pApplicationName   = "Hello Vulkan",
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName        = "No Engine",
            .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion         = vk::ApiVersion14
        };

        std::vector<char const*> requiredLayers;
        if (!ndebug) {
            requiredLayers.assign(validationLayers.begin(), validationLayers.end());

            auto layerProperties = context.enumerateInstanceLayerProperties();
            if (std::ranges::any_of(requiredLayers, [&layerProperties](auto const& requiredLayer) {
                return std::ranges::none_of(layerProperties,
                                           [requiredLayer](auto const& layerProperty)
                                           { return strcmp(layerProperty.layerName, requiredLayer) == 0; });
            }))
            {
                throw std::runtime_error("One or more required layers are not supported!");
            }
        }

        uint32_t glfwExtensionCount = 0;
        auto     glfwExtensions     = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        
        auto extensionProperties = context.enumerateInstanceExtensionProperties();
        for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
            if (std::ranges::none_of(extensionProperties, [glfwExtension = glfwExtensions[i]](auto const &extensionProperty) { return strcmp(extensionProperty.extensionName, glfwExtension) == 0; })) {
                throw std::runtime_error("Required GLFW extension not supported: " + std::string(glfwExtensions[i]));
            }
        }
        
        vk::InstanceCreateInfo createInfo {
            .pApplicationInfo        = &appInfo,
            .enabledExtensionCount   = glfwExtensionCount,
            .ppEnabledExtensionNames = glfwExtensions
        };
        
        instance = vk::raii::Instance(context, createInfo);
    }

    [[nodiscard]] bool initialized() const { return instance != nullptr; }

    void run() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    ~Window() {
        glfwDestroyWindow(window);
    }
};
    
int main() {
    if (!ndebug) { std::cerr << "[N] Debug build!" << std::endl; }
    if (!init()) {
        std::cerr << ":(  Failed to init" << std::endl;
        return EXIT_FAILURE;
    }
    auto* window = new Window();
    if (!window->initialized()) {
        std::cerr << ":(  Failed to init window" << std::endl;
        return EXIT_FAILURE;
    }
    window->run();
    delete window;
    cleanup();
    std::cout << "Bye!" << std::endl;
    return EXIT_SUCCESS;
}