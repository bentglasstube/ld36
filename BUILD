package(default_visibility = ["//visibility:public"])
load("@mxebzl//tools/windows:rules.bzl", "pkg_winzip")

cc_binary(
    name = "catapults",
    data = ["//content"],
    linkopts = [
        "-lSDL2main",
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
