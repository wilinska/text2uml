load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "edges_mapper",
    srcs = ["edges_mapper.cpp"],
    hdrs = ["edges_mapper.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/image_builder/mapper:i_mapper",
    ],
)
