#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_I_LAYOUT_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_I_LAYOUT_HPP

#include "src/cpp/config/config.hpp"
#include "src/cpp/graph/graph.hpp"
#include <iostream>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/fileformats/GraphIO.h>
#include <sstream>
#include <string>

class ILayout
{
public:
  ILayout(Graph &graph);

  virtual ~ILayout() = default;

  std::string GenerateSVG(const Config &config);

  Graph &graph;
  ogdf::Graph G;
  ogdf::GraphAttributes GA;
  std::optional<ogdf::NodeArray<std::string>> swimlane_map;
  std::unordered_map<std::string, std::pair<double, double>> swimlane_min_max;
  std::unordered_map<std::uint64_t, ogdf::node> id_to_node_map;

protected:
  void ApplyNodeTransformations(ogdf::Graph &G, ogdf::GraphAttributes &GA);
  double StringToDouble(const char *str);

  virtual void ApplyLayout(const Config &config) = 0;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_I_LAYOUT_HPP
