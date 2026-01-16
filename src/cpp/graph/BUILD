cc_library(
    name = "graph",
    hdrs = [
        "edge.hpp",
        "graph.hpp",
        "node.hpp",
        "object.hpp",
        "swimlane_config.hpp",
    ],
    copts = ["-std=c++17"],
    features = ["c++17"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/cpp/graph/enums:activity_type_enum",
        "//src/cpp/graph/enums:line_head_enum",
        "//src/cpp/graph/enums:line_type_enum",
        "//src/cpp/graph/enums:node_type_enum",
    ],
)
