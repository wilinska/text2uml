load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "decorated_parser_builder",
    srcs = ["decorated_parser_builder.cpp"],
    hdrs = ["decorated_parser_builder.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/parser:i_parser",
        "//src/cpp/parser/decorators:graphical_parser",
    ],
)
