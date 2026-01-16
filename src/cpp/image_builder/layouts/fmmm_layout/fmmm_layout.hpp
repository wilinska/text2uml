#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_FMMM_LAYOUT_FMMM_LAYOUT_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_FMMM_LAYOUT_FMMM_LAYOUT_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"

class FMMMGraphLayout : public ILayout
{
public:
  FMMMGraphLayout(Graph &graph) : ILayout(graph) {}

  virtual ~FMMMGraphLayout() = default;

protected:
  void ApplyLayout(const Config &config) override;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_FMMM_LAYOUT_FMMM_LAYOUT_HPP
