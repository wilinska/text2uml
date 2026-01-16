load("@rules_cc//cc:defs.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "graphical_parser_tests",
    srcs = ["graphical_parser_tests.cpp"],
    features = [
        "additional_warnings",
        "strict_clang_tidy_warnings",
        "strict_warnings",
    ],
    deps = [
        "//src/cpp/parser/decorators:graphical_parser",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
