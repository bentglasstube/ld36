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
        "//src/framework:audio",
        "//src/framework:graphics",
        "//src/framework:input",
        "//src/framework:particle",
        "//src/framework:screen",
        "//src/framework:text",
    ],
)

cc_library(
    name = "boulder",
    srcs = ["boulder.cc"],
    hdrs = ["boulder.h"],
    deps = ["//src/framework:graphics"],
)

cc_library(
    name = "catapult",
    srcs = ["catapult.cc"],
    hdrs = ["catapult.h"],
    deps = [
        ":map",
        "//src/framework:graphics",
        "//src/framework:input",
        "//src/framework:spritemap",
    ],
)

cc_library(
    name = "clouds",
    srcs = ["clouds.cc"],
    hdrs = [
        "clouds.h",
        "stb_perlin.h",
    ],
    deps = ["//src/framework:graphics"],
)

cc_library(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":title_screen",
        "//src/framework:game",
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
        "//src/framework:graphics",
        "//src/framework:text",
    ],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        ":map",
        "//src/framework:audio",
        "//src/framework:spritemap",
    ],
)

cc_library(
    name = "title_screen",
    srcs = ["title_screen.cc"],
    hdrs = ["title_screen.h"],
    deps = [
        ":battle_screen",
        "//src/framework:backdrop",
        "//src/framework:screen",
    ],
)
