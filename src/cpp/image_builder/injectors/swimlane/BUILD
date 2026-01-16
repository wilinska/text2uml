load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "swimlane_injector",
    srcs = ["swimlane_injector.cpp"],
    hdrs = ["swimlane_injector.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/image_builder/injectors:i_injector",
        "//src/cpp/image_builder/mapper",
        "//src/cpp/utils/text:utils",
    ],
)
