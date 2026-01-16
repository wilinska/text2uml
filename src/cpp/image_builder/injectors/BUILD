load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "i_injector",
    hdrs = [
        "i_injector.hpp",
    ],
    # copts = [
    #     # "-I/usr/include/freetype2",
    #     # "-I/usr/include/libpng16",
    # ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    # inkopts = ["-lfreetype"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/graph",
        "//src/cpp/image_builder/mapper",
        #"//third_party/freetype2/freetype",
        "@tinyxml2",
    ],
)

cc_library(
    name = "i_content_injector",
    hdrs = ["i_content_injector.hpp"],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
)
