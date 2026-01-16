#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_TREE_LAYOUT_TREE_LAYOUT_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_TREE_LAYOUT_TREE_LAYOUT_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"

class TreeGraphLayout : public ILayout
{
public:
  TreeGraphLayout(Graph &graph) : ILayout(graph) {}

  virtual ~TreeGraphLayout() = default;

protected:
  void ApplyLayout(const Config &config) override;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_TREE_LAYOUT_TREE_LAYOUT_HPP
