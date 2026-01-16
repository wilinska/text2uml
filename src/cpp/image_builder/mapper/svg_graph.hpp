#ifndef SRC_CPP_IMAGE_BUILDER_MAPPER_SVG_GRAPH_HPP
#define SRC_CPP_IMAGE_BUILDER_MAPPER_SVG_GRAPH_HPP

#include "src/cpp/graph/graph.hpp"
#include "tinyxml2.h"
#include <iostream>

using XMLElementPtr = tinyxml2::XMLElement *;
using XMLDocument = tinyxml2::XMLDocument;

struct SVGNode
{
  XMLElementPtr parent;
  XMLElementPtr box;
  XMLElementPtr text;
};

struct SVGEdge
{
  XMLElementPtr parent;
  XMLElementPtr line;
  XMLElementPtr text;
  XMLElementPtr reversed_line;
};

class SVGGraph
{
public:
  using Id = std::uint64_t;
  using SVGNodeMap = std::unordered_map<Id, SVGNode>;
  using SVGEdgeMap = std::unordered_map<Id, SVGEdge>;

  SVGGraph(const std::string &svg_graph, const Graph &graph) : graph_{graph}
  {
    if (doc_.Parse(svg_graph.c_str()) != tinyxml2::XML_SUCCESS)
    {
      std::cerr << "Failed to parse." << std::endl;
    }
  }

  XMLDocument &GetDocument() { return doc_; }
  SVGNodeMap &GetNodesMap() { return nodes_map_; }
  SVGEdgeMap &GetEdgesMap() { return edges_map_; }

  const Graph &graph_;
  XMLDocument doc_;

  SVGNodeMap nodes_map_;
  SVGEdgeMap edges_map_;
};

#endif // SRC_CPP_IMAGE_BUILDER_MAPPER_SVG_GRAPH_HPP
