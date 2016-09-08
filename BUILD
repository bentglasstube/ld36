package(default_visibility = ["//visibility:public"])
load("//tools/windows:winzip.bzl", "winzip")

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

winzip(
    name = "catapults-windows-pkg",
    srcs = [
        ":catapults",
        "//content",
    ],
    zipfile = "catapults-windows.zip",
)
