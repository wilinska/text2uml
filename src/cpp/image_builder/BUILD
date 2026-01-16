load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "image_builder",
    srcs = ["image_builder.cpp"],
    hdrs = ["image_builder.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/graph",
        "//src/cpp/image_builder/injectors/content:content_injector",
        "//src/cpp/image_builder/layouts:i_layout",
        "//src/cpp/image_builder/mapper",
    ],
)
