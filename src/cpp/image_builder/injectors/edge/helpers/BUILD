load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "helpers",
    srcs = [
        "bezier_helper.cpp",
        "path_helper.cpp",
        "path_move_helper.cpp",
    ],
    hdrs = [
        "bezier_helper.hpp",
        "path_helper.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/graph",
        "//src/cpp/utils/geometry:utils",
    ],
)
