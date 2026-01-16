load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "optimal_hierarchy_layout",
    srcs = ["optimal_hierarchy_layout.cpp"],
    hdrs = ["optimal_hierarchy_layout.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    includes = ["@ogdf//:include"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/image_builder/layouts:i_layout",
        "@ogdf",
    ],
)
