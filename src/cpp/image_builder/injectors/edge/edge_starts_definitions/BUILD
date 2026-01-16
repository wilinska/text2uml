load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "edge_starts_definitions",
    hdrs = [
        "arrow_injector.hpp",
        "circle_injector.hpp",
        "open_arrow_injector.hpp",
        "open_rhomb_injector.hpp",
        "rhomb_injector.hpp",
        "square_injector.hpp",
        "three_lines_injector.hpp",
        "x_injector.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/image_builder/injectors:i_injector",
        "@tinyxml2",
    ],
)
