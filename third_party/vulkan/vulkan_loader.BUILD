# load("@bazel//tools/build_defs/repo:http.bzl", "http_file")

# VSWHERE_VERSION = "3.1.7"

# you're never gonna believe this
# http_file(
#     name = "vswhere",
#     url = "https://github.com/microsoft/vswhere/releases/download/{}/vswhere.exe".format(VSWHERE_VERSION),
#     sha1 = "E3FA9B2DB259D8875170717469779EA1280C8466",
#     executable = True,
# )

# it's a shame the cmakelists.txts in Vulkan-Loader are a fuckin mess, infinitely easier to just call cmake :(
# (this one needs to be built with cmake too since the loader is, but this *should* be reproducable anywhere)
# genrule(
#     name = "loader",
#     cmd = "cmake -S $(location :vulkan_loader_archive) -B ../out -G Ninja -D VULKAN_HEADERS_INSTALL_DIR=$(rlocationpath @vulkan_headers_archive//:headers)/../srcs && Ninja -C ../out",
#     cmd_bat = "\
#         for /f \"usebackq delims=\" %%i in (`$(exe :vswhere) -property installationPath`) do ( %%i/VC/Auxiliary/Build/vcvarsall.bat x64 ) && \
#         cmake -S $(location :vulkan_loader_archive) -B ../out -G Ninja -D VULKAN_HEADERS_INSTALL_DIR=$(location :headers)/../srcs && Ninja -C ../out",
#     outs = select({
#         "@prelude//os:windows": ["loader/vulkan-1.lib"],
#         "DEFAULT": ["loader/vulkan-1.a"],  #TODO FIX
#     }),
# )

# genrule(
#     name = "b",
#     srcs = ["@vulkan_headers_archive//:headers"],
#     cmd_bat = """
    
#     echo $(locations @vulkan_headers_archive//:headers) > $@
    
#     """,
#     outs = ["a.txt"],
# )

# add a cc_library here

NORMAL_LOADER_SRCS = [
    "allocation.c",
    "allocation.h",
    "cJSON.c",
    "cJSON.h",
    "debug_utils.c",
    "debug_utils.h",
    "extension_manual.c",
    "extension_manual.h",
    "loader_environment.c",
    "loader_environment.h",
    "gpa_helper.c",
    "gpa_helper.h",
    "loader.c",
    "loader.h",
    "log.c",
    "log.h",
    "loader_json.c",
    "loader_json.h",
    "settings.c",
    "settings.h",
    "terminator.c",
    "trampoline.c",
    "unknown_function_handling.c",
    "unknown_function_handling.h",
    "wsi.c",
    "wsi.h",
]

WIN32_LOADER_SRCS = ["loader_windows.c", "dirent_on_windows.c"],

YOU_SHOULD_MIT_YOURSELF_NOW_LOADER_SRCS = ["loader_linux.c"],  # linux

OPT_LOADER_SRCS = ["dev_ext_trampoline.c", "phys_dev_ext.c"],


# prebuilt_cxx_library(
#     name = "vulkan",
#     static_lib = ":loader",
#     header_namespace = "",
#     exported_headers = "@:vulkan_headers_archive//:vulkan_headers",
#     preferred_linkage = "static",
#     visibility = ["PUBLIC"],
# )
