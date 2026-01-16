#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_OPTIMAL_HIERARCHY_LAYOUT_OPTIMAL_HIERARCHY_LAYOUT_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_OPTIMAL_HIERARCHY_LAYOUT_OPTIMAL_HIERARCHY_LAYOUT_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"

class OptimalHierarchyGraphLayout : public ILayout
{
public:
  OptimalHierarchyGraphLayout(Graph &graph) : ILayout(graph) {}

  virtual ~OptimalHierarchyGraphLayout() = default;

protected:
  void ApplyLayout(const Config &config) override;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_OPTIMAL_HIERARCHY_LAYOUT_OPTIMAL_HIERARCHY_LAYOUT_HPP
