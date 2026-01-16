#include "src/cpp/image_builder/mapper/mapper.hpp"
#include <iostream>

using XMLElementPtr = tinyxml2::XMLElement *;
using XMLDocument = tinyxml2::XMLDocument;

Mapper::Mapper(SVGGraph &svg_graph)
    : graph_{svg_graph.graph_},
      doc_{svg_graph.doc_},
      nodes_map_{svg_graph.nodes_map_},
      edges_map_{svg_graph.edges_map_},
      nodes_mapper_{doc_.RootElement(), nodes_map_},
      edges_mapper_{graph_,
                    doc_.RootElement()->FirstChildElement(TAG_G),
                    nodes_map_,
                    edges_map_}
{
}

void Mapper::Map()
{
  XMLElementPtr root = doc_.RootElement();
  if (!root)
  {
    std::cerr << "Failed to load root element." << std::endl;
  }

  nodes_mapper_.Map();
  edges_mapper_.Map();
}
