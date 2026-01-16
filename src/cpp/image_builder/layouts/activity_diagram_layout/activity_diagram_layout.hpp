#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_ACTIVITY_DIAGRAM_LAYOUT_ACTIVITY_DIAGRAM_LAYOUT_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_ACTIVITY_DIAGRAM_LAYOUT_ACTIVITY_DIAGRAM_LAYOUT_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"

class ActivityDiagramLayout : public ILayout
{
public:
  ActivityDiagramLayout(Graph &graph) : ILayout(graph) {}

  virtual ~ActivityDiagramLayout() = default;

  void
  CreateHorizontalSwimlaneLayout(ogdf::Graph &G,
                                 ogdf::GraphAttributes &GA,
                                 ogdf::NodeArray<std::string> &swimlaneMap);

protected:
  void ApplyLayout(const Config &config) override;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_ACTIVITY_DIAGRAM_LAYOUT_ACTIVITY_DIAGRAM_LAYOUT_HPP
