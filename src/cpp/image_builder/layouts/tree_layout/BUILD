load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "tree_layout",
    srcs = ["tree_layout.cpp"],
    hdrs = ["tree_layout.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    includes = ["@ogdf//:include"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/image_builder/layouts:i_layout",
        "@ogdf",
    ],
)
