#ifndef SRC_CPP_IMAGE_BUILDER_MAPPER_MAPPER_HPP
#define SRC_CPP_IMAGE_BUILDER_MAPPER_MAPPER_HPP

#include "src/cpp/image_builder/mapper/edges/edges_mapper.hpp"
#include "src/cpp/image_builder/mapper/nodes/nodes_mapper.hpp"

using XMLDocument = tinyxml2::XMLDocument;

class Mapper : IMapper
{
public:
  Mapper(SVGGraph &svg_graph);

  void Map();

private:
  const Graph &graph_;
  XMLDocument &doc_;

  SVGNodeMap &nodes_map_;
  SVGEdgeMap &edges_map_;

  NodesMapper nodes_mapper_;
  EdgesMapper edges_mapper_;
};

#endif // SRC_CPP_IMAGE_BUILDER_MAPPER_MAPPER_HPP
