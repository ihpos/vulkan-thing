load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

VULKAN_SDK_VERSION = "1.4.336"
VOLK_VERSION = "50ad19da721d502132f06721b4a290270e303e68"

def _deps_impl(module_ctx):
    root = module_ctx.path(Label("//:MODULE.bazel")).dirname

    http_archive(
        name = "vulkan_headers_archive",
        url = "https://github.com/KhronosGroup/Vulkan-Headers/archive/refs/tags/v{}.zip".format(VULKAN_SDK_VERSION),
        strip_prefix = "Vulkan-Headers-{}".format(VULKAN_SDK_VERSION),
        build_file = ":vulkan_headers.bazel",
    )

    http_archive(
        name = "vulkan_hpp_headers_archive",
        url = "https://github.com/KhronosGroup/Vulkan-Hpp/archive/refs/tags/v{}.zip".format(VULKAN_SDK_VERSION),
        strip_prefix = "Vulkan-Hpp-{}".format(VULKAN_SDK_VERSION),
        build_file = ":vulkan_hpp.bazel",
    )

    # http_archive(
    #     name = "vulkan_loader_archive",
    #     url = "https://github.com/KhronosGroup/Vulkan-Loader/archive/refs/tags/vulkan-sdk-{}.0.zip".format(VULKAN_SDK_VERSION),
    #     strip_prefix = "Vulkan-Loader-vulkan-sdk-{}.0".format(VULKAN_SDK_VERSION),
    #     build_file = ":vulkan_loader.bazel"
    # )

    http_archive(
        name = "volk",
        url = "https://github.com/zeux/volk/archive/{}.zip".format(VOLK_VERSION),
        strip_prefix = "volk-{}".format(VOLK_VERSION),
        build_file = ":volk.bazel",
    )

deps = module_extension(implementation = _deps_impl)