#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_SUGIYAMA_LAYOUT_SUGIYAMA_LAYOUT_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_SUGIYAMA_LAYOUT_SUGIYAMA_LAYOUT_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"

class SugiyamaGraphLayout : public ILayout
{
public:
  SugiyamaGraphLayout(Graph &graph) : ILayout(graph) {}

  virtual ~SugiyamaGraphLayout() = default;

protected:
  void ApplyLayout(const Config &config) override;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_SUGIYAMA_LAYOUT_SUGIYAMA_LAYOUT_HPP
