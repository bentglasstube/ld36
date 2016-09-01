package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "catapults",
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_mixer",
        "-lm",
    ],
    deps = ["//src:main"],
)
