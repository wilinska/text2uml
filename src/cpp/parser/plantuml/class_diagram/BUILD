load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "parser",
    srcs = [
        "parser.cpp",
    ],
    hdrs = [
        "parser.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/parser:i_parser",
        "//src/cpp/parser/plantuml/class_diagram/generated_parser",
        "//src/cpp/parser/plantuml/helpers",
    ],
)
