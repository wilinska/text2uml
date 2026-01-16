load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node_injector",
    srcs = ["node_injector.cpp"],
    hdrs = [
        "node_injector.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    # copts = [
    #     # "-I/usr/include/freetype2",
    #     # "-I/usr/include/libpng16",
    # ],
    # inkopts = ["-lfreetype"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/graph",
        "//src/cpp/image_builder/injectors:i_injector",
        "//src/cpp/image_builder/mapper",
        #"//third_party/freetype2/freetype",
        "//src/cpp/utils/text:utils",
        "@tinyxml2",
    ],
)
