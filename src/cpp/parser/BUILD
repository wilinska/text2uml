load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "i_parser",
    hdrs = [
        "i_parser.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = ["//src/cpp/graph"],
)
