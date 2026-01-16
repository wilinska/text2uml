load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "parser",
    srcs = [
        "conditional_statement_parser.cpp",
        "fork_statement_parser.cpp",
        "group_statement_parser.cpp",
        "parser.cpp",
        "partition_statement_parser.cpp",
        "repeat_statement_parser.cpp",
        "split_statement_parser.cpp",
        "swimlane_statement_parser.cpp",
        "switch_statement_parser.cpp",
        "while_statement_parser.cpp",
    ],
    hdrs = [
        "parser.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/parser:i_parser",
        "//src/cpp/parser/plantuml/activity_diagram/generated_parser",
        "//src/cpp/parser/plantuml/helpers",
    ],
)
