#define VK_NO_PROTOTYPES
#include <volk/volk.h>
#undef VK_NO_PROTOTYPES

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>
// import vulkan;  // Needs a working LLVM toolchain (this is Bazel's fault, not MSVC's)

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

import glm;

namespace ui {
    bool init();
    void cleanup();

    class Window {
        GLFWwindow* window = nullptr;
        vk::raii::Context context;
        vk::raii::Instance instance = nullptr;
        constexpr static int WIDTH = 800;
        constexpr static int HEIGHT = 600;

    public:
        Window();
        bool initialized() const;
        void run();
        ~Window();
    };
}