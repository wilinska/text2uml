load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "activity_diagram_layout",
    srcs = [
        "activity_diagram_layout.cpp",
        "activity_ranking.cpp",
    ],
    hdrs = [
        "activity_diagram_layout.hpp",
        "activity_ranking.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    includes = ["@ogdf//:include"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/image_builder/layouts:i_layout",
        "@ogdf",
    ],
)
