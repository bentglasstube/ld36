package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "catapults",
    linkopts = [
        "-lSDL2",
        "-lSDL2_mixer",
    ],
    deps = ["//src:main"],
    data = ["//content:content"],
)
