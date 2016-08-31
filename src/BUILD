package(default_visibility = ["//visibility:public"])

cc_library(
    name = "audio",
    srcs = ["audio.cc"],
    hdrs = ["audio.h"],
)

cc_library(
    name = "backdrop",
    srcs = ["backdrop.cc"],
    hdrs = ["backdrop.h"],
    deps = [":graphics"],
)

cc_library(
    name = "battle_screen",
    srcs = ["battle_screen.cc"],
    hdrs = ["battle_screen.h"],
    deps = [
        ":audio",
        ":boulder",
        ":catapult",
        ":clouds",
        ":graphics",
        ":input",
        ":map",
        ":particle",
        ":screen",
        ":text",
    ],
)

cc_library(
    name = "boulder",
    srcs = ["boulder.cc"],
    hdrs = ["boulder.h"],
    deps = [":graphics"],
)

cc_library(
    name = "catapult",
    srcs = ["catapult.cc"],
    hdrs = ["catapult.h"],
    deps = [
        ":graphics",
        ":input",
        ":map",
        ":spritemap",
    ],
)

cc_library(
    name = "clouds",
    srcs = ["clouds.cc"],
    hdrs = [
        "clouds.h",
        "stb_perlin.h",
    ],
    deps = [":graphics"],
)

cc_library(
    name = "game",
    srcs = ["game.cc"],
    hdrs = ["game.h"],
    deps = [
        ":text",
        ":title_screen",
    ],
)

cc_library(
    name = "graphics",
    srcs = ["graphics.cc"],
    hdrs = ["graphics.h"],
)

cc_library(
    name = "input",
    srcs = ["input.cc"],
    hdrs = ["input.h"],
)

cc_library(
    name = "main",
    srcs = ["main.cc"],
    deps = [":game"],
)

cc_library(
    name = "map",
    srcs = ["map.cc"],
    hdrs = [
        "map.h",
        "stb_perlin.h",
    ],
    deps = [
        ":graphics",
        ":text",
    ],
)

cc_library(
    name = "particle",
    srcs = ["particle.cc"],
    hdrs = ["particle.h"],
    deps = [":graphics"],
)

cc_library(
    name = "player",
    srcs = ["player.cc"],
    hdrs = ["player.h"],
    deps = [
        ":audio",
        ":map",
        ":sprite",
        ":spritemap",
    ],
)

cc_library(
    name = "screen",
    srcs = ["screen.cc"],
    hdrs = ["screen.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
    ],
)

cc_library(
    name = "sprite",
    srcs = ["sprite.cc"],
    hdrs = ["sprite.h"],
    deps = [":graphics"],
)

cc_library(
    name = "spritemap",
    srcs = ["spritemap.cc"],
    hdrs = ["spritemap.h"],
    deps = [":graphics"],
)

cc_library(
    name = "text",
    srcs = ["text.cc"],
    hdrs = ["text.h"],
    deps = [":graphics"],
)

cc_library(
    name = "title_screen",
    srcs = ["title_screen.cc"],
    hdrs = ["title_screen.h"],
    deps = [
        ":backdrop",
        ":battle_screen",
        ":screen",
    ],
)
