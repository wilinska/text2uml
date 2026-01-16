load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "content_injector",
    srcs = ["content_injector.cpp"],
    hdrs = [
        "content_injector.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/graph",
        "//src/cpp/image_builder/injectors/edge:edge_injector",
        "//src/cpp/image_builder/injectors/node:node_injector",
        "//src/cpp/image_builder/injectors/swimlane:swimlane_injector",
        "//src/cpp/image_builder/mapper",
        "@tinyxml2",
    ],
)
