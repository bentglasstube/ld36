package(default_visibility = ["//visibility:public"])

cc_library(
    name = "battle_screen",
    srcs = ["battle_screen.cc"],
    hdrs = ["battle_screen.h"],
    deps = [
        ":boulder",
        ":catapult",
        ":clouds",
        ":map",
        "@libgam//:audio",
        "@libgam//:graphics",
        "@libgam//:input",
        "@libgam//:particle",
        "@libgam//:screen",
        "@libgam//:text",
    ],
)

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
        ":title_screen",
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
    name = "title_screen",
    srcs = ["title_screen.cc"],
    hdrs = ["title_screen.h"],
    deps = [
        ":battle_screen",
        "@libgam//:backdrop",
        "@libgam//:menu",
        "@libgam//:screen",
    ],
)
