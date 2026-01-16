#ifndef SRC_CPP_IMAGE_BUILDER_MAPPER_NODES_NODES_MAPPER_HPP
#define SRC_CPP_IMAGE_BUILDER_MAPPER_NODES_NODES_MAPPER_HPP

#include "src/cpp/image_builder/mapper/i_mapper.hpp"

class NodesMapper : public IMapper
{
public:
  NodesMapper(const XMLElementPtr root,
              std::unordered_map<std::uint64_t, SVGNode> &nodes_map);

  void Map();

private:
  XMLElementPtr root_;
  std::unordered_map<std::uint64_t, SVGNode> &nodes_map_;
};

#endif // SRC_CPP_IMAGE_BUILDER_MAPPER_NODES_NODES_MAPPER_HPP
