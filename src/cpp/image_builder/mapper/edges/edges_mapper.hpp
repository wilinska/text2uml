#ifndef SRC_CPP_IMAGE_BUILDER_MAPPER_EDGES_EDGES_MAPPER_HPP
#define SRC_CPP_IMAGE_BUILDER_MAPPER_EDGES_EDGES_MAPPER_HPP

#include "src/cpp/image_builder/mapper/i_mapper.hpp"

class EdgesMapper : public IMapper
{
public:
  EdgesMapper(const Graph &graph,
              const XMLElementPtr root,
              const SVGNodeMap &nodes_map,
              SVGEdgeMap &edge_map);

  void Map();

private:
  const Graph &graph_;
  XMLElementPtr root_;
  const SVGNodeMap &nodes_map_;

  SVGEdgeMap &edges_map_;
};

#endif // SRC_CPP_IMAGE_BUILDER_MAPPER_EDGES_EDGES_MAPPER_HPP
