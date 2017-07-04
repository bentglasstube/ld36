package(default_visibility = ["//visibility:public"])
load("@mxebzl//tools/windows:rules.bzl", "pkg_winzip")

config_setting(
    name = "windows",
    values = {
        "crosstool_top": "@mxebzl//tools/windows:toolchain",
    }
)

cc_binary(
    name = "catapults",
    data = ["//content"],
    linkopts = select({
        ":windows": ["-mwindows", "-lSDL2main"],
        "//conditions:default": [],
    }) + [
        "-lSDL2",
        "-lSDL2_mixer",
        "-lm",
    ],
    deps = ["//src:main"],
)

pkg_winzip(
    name = "catapults-windows",
    files = [
        ":catapults",
        "//content",
    ],
)
