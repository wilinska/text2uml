load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "i_layout",
    srcs = ["i_layout.cpp"],
    hdrs = ["i_layout.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    includes = ["@ogdf//:include"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/config",
        "//src/cpp/graph",
        "@ogdf",
    ],
)

cc_library(
    name = "layout_type",
    hdrs = ["layout_type.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "layout_builder",
    hdrs = ["layout_builder.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    # includes = ["@ogdf//:include"],
    visibility = ["//visibility:public"],
    deps = [
        ":i_layout",
        ":layout_type",
        "//src/cpp/graph",
        "//src/cpp/image_builder/layouts/activity_diagram_layout",
        "//src/cpp/image_builder/layouts/circular_layout",
        "//src/cpp/image_builder/layouts/fmmm_layout",
        "//src/cpp/image_builder/layouts/optimal_hierarchy_layout",
        "//src/cpp/image_builder/layouts/orthogonal_layout",
        "//src/cpp/image_builder/layouts/sugiyama_layout",
        "//src/cpp/image_builder/layouts/tree_layout",
    ],
)
