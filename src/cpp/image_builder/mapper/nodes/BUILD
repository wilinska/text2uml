load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "nodes_mapper",
    srcs = ["nodes_mapper.cpp"],
    hdrs = ["nodes_mapper.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/image_builder/mapper:i_mapper",
    ],
)
