load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "generated_parser",
    srcs = [
        "generated_parser.cpp",
        "lex.yy.cpp",
        "parser.tab.cpp",
    ],
    hdrs = [
        "generated_parser.hpp",
        "parser.tab.h",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//src/cpp/parser/plantuml/activity_diagram:__subpackages__"],
)
