load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "svg_graph",
    hdrs = ["svg_graph.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/graph",
        "@tinyxml2",
    ],
)

cc_library(
    name = "i_mapper",
    hdrs = [
        "i_mapper.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    includes = ["@tinyxml2//:include"],
    visibility = ["//visibility:public"],
    deps = [
        ":svg_graph",
        "//src/cpp/utils/geometry:utils",
    ],
)

cc_library(
    name = "mapper",
    srcs = ["mapper.cpp"],
    hdrs = [
        "mapper.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        ":i_mapper",
        ":svg_graph",
        "//src/cpp/image_builder/mapper/edges:edges_mapper",
        "//src/cpp/image_builder/mapper/nodes:nodes_mapper",
    ],
)
