#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_CIRCULAR_LAYOUT_CIRCULAR_LAYOUT_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_CIRCULAR_LAYOUT_CIRCULAR_LAYOUT_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"

class CircularGraphLayout : public ILayout
{
public:
  CircularGraphLayout(Graph &graph) : ILayout(graph) {}

  virtual ~CircularGraphLayout() = default;

protected:
  void ApplyLayout(const Config &config) override;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_CIRCULAR_LAYOUT_CIRCULAR_LAYOUT_HPP
