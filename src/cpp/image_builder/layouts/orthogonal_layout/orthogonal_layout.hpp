#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_ORTHOGONAL_LAYOUT_ORTHOGONAL_LAYOUT_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_ORTHOGONAL_LAYOUT_ORTHOGONAL_LAYOUT_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"

class OrthogonalGraphLayout : public ILayout
{
public:
  OrthogonalGraphLayout(Graph &graph) : ILayout(graph) {}

  virtual ~OrthogonalGraphLayout() = default;

protected:
  void ApplyLayout(const Config &config) override;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_ORTHOGONAL_LAYOUT_ORTHOGONAL_LAYOUT_HPP
