load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:local.bzl", "local_repository")

GLM_VERSION = "1.0.1"
GLFW_VERSION = "3.4"

def _deps_impl(module_ctx):
    root = module_ctx.path(Label("//:MODULE.bazel")).dirname

    http_archive(
        name = "glm",
        urls = ["https://github.com/g-truc/glm/archive/refs/tags/{}.zip".format(GLM_VERSION)],
        strip_prefix = "glm-{}".format(GLM_VERSION),
        build_file = ":glm.bazel",
    )

    http_archive(
        name = "glfw",
        urls = ["https://github.com/glfw/glfw/archive/refs/tags/{}.zip".format(GLFW_VERSION)],
        strip_prefix = "glfw-{}".format(GLFW_VERSION),
        build_file = ":glfw.bazel",
    )

    local_repository(name = "vulkan", path = str(root.get_child("vulkan")))

deps = module_extension(implementation = _deps_impl)