load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "generator",
    srcs = ["generator.cpp"],
    hdrs = ["generator.hpp"],
    copts = [
        "-std=c++17",
    ],
    deps = [
        "//src/cpp/config",
        "//src/cpp/image_builder",
        "//src/cpp/image_builder/layouts:layout_builder",
        "//src/cpp/parser/builders:decorated_parser_builder",
        "//src/cpp/parser/plantuml/activity_diagram:parser",
        "//src/cpp/parser/plantuml/class_diagram:parser",
    ],
)
