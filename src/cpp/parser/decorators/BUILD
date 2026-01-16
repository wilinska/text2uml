load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "graphical_parser",
    srcs = ["graphical_parser.cpp"],
    hdrs = ["graphical_parser.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/parser:i_parser",
        "//src/cpp/utils/text:utils",
    ],
)
