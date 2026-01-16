load("@rules_cc//cc:defs.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "builder_tests",
    srcs = ["builder_tests.cpp"],
    features = [
        "additional_warnings",
        "strict_clang_tidy_warnings",
        "strict_warnings",
    ],
    deps = [
        "//src/cpp/parser/builders:decorated_parser_builder",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
