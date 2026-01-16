load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "edge_bending_type",
    hdrs = ["edge_bending_type.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "edge_head_injector",
    hdrs = [
        "edge_head_injector.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/image_builder/injectors:i_injector",
        "//src/cpp/image_builder/injectors/edge/edge_ends_definitions",
        "//src/cpp/image_builder/injectors/edge/edge_starts_definitions",
        "@tinyxml2",
    ],
)

cc_library(
    name = "edge_injector",
    srcs = ["edge_injector.cpp"],
    hdrs = [
        "edge_injector.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        ":edge_bending_type",
        ":edge_head_injector",
        "//src/cpp/image_builder/injectors:i_injector",
        "//src/cpp/image_builder/injectors/edge/helpers",
    ],
)
