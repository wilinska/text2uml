#ifndef SRC_CPP_IMAGE_BUILDER_IMAGE_BUILDER_HPP
#define SRC_CPP_IMAGE_BUILDER_IMAGE_BUILDER_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"
#include <memory>

class ImageBuilder
{
public:
  std::string GenerateImage(const std::string &edge_bends,
                            const Graph &graph,
                            const std::shared_ptr<ILayout> layout,
                            const Config &config);
};

#endif // SRC_CPP_IMAGE_BUILDER_IMAGE_BUILDER_HPP
