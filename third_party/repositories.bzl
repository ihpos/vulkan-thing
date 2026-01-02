load("@bazel_tools//tools/build_defs/repo:local.bzl", "local_repository")

def _deps_impl(module_ctx):
    root = module_ctx.path(Label("//:MODULE.bazel")).dirname

    local_repository(name = "vulkan", path = str(root.get_child("vulkan")))

deps = module_extension(implementation = _deps_impl)