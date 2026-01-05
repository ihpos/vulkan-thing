#include <algorithm>
#include <cstdlib>
#include <memory>
#include <stdexcept>

#include "ui.hpp"

#ifdef NDEBUG
constexpr bool ndebug = true;
#else
constexpr bool ndebug = false;
#endif

namespace ui {
    constexpr vk::ApplicationInfo appInfo{
        .pApplicationName   = "Hello Vulkan",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName        = "No Engine",
        .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion         = vk::ApiVersion14
    };

    const std::vector<char const*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

    bool init() {
        if (!glfwInit()) { return false; }
        if (!glfwVulkanSupported()) { return false; }
        if (volkInitialize() != VK_SUCCESS) { return false; }
        return true;
    }

    void cleanup() {
        glfwTerminate();
        volkFinalize();
    }

    Window::Window() {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

        if (!ndebug) {
            auto layerProperties = context.enumerateInstanceLayerProperties();
            if (std::ranges::any_of(validationLayers, [&layerProperties](auto const& requiredLayer) {
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
#ifndef NDEBUG
            .enabledLayerCount       = static_cast<uint32_t>(validationLayers.size()),
            .ppEnabledLayerNames     = validationLayers.data(),
#endif
            .enabledExtensionCount   = glfwExtensionCount,
            .ppEnabledExtensionNames = glfwExtensions
        };

        instance = vk::raii::Instance(context, createInfo);
    }

    bool Window::initialized() const { return instance != nullptr; }

    void Window::run() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    Window::~Window() {
        glfwDestroyWindow(window);
    }
}