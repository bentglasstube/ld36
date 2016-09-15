package(default_visibility = ["//visibility:public"])

cc_library(
    name = "boulder",
    srcs = ["boulder.cc"],
    hdrs = ["boulder.h"],
    deps = ["@libgam//:graphics"],
)

cc_library(
    name = "catapult",
    srcs = ["catapult.cc"],
    hdrs = ["catapult.h"],
    deps = [
        ":map",
        "@libgam//:graphics",
        "@libgam//:input",
        "@libgam//:spritemap",
    ],
)

cc_library(
    name = "clouds",
    srcs = ["clouds.cc"],
    hdrs = [
        "clouds.h",
        "stb_perlin.h",
    ],
    deps = ["@libgam//:graphics"],
)

cc_library(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":screens",
        "@libgam//:game",
    ],
)

cc_library(
    name = "map",
    srcs = ["map.cc"],
    hdrs = [
        "map.h",
        "stb_perlin.h",
    ],
    deps = [
        "@libgam//:graphics",
        "@libgam//:text",
    ],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        ":map",
        "@libgam//:audio",
        "@libgam//:spritemap",
    ],
)

cc_library(
    name = "screens",
    srcs = [
        "battle_screen.cc",
        "title_screen.cc",
    ],
    hdrs = [
        "battle_screen.h",
        "title_screen.h",
    ],
    deps = [
        ":boulder",
        ":catapult",
        ":clouds",
        ":map",
        ":target",
        "@libgam//:audio",
        "@libgam//:backdrop",
        "@libgam//:graphics",
        "@libgam//:input",
        "@libgam//:menu",
        "@libgam//:particle",
        "@libgam//:screen",
        "@libgam//:text",
    ],
)

cc_library(
    name = "target",
    srcs = ["target.cc"],
    hdrs = ["target.h"],
    deps = [
        "@libgam//:graphics",
        "@libgam//:sprite",
    ],
)
