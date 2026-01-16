#include "src/cpp/image_builder/mapper/edges/edges_mapper.hpp"
#include <ostream>
#include <regex>

namespace
{
std::regex PATH_PATTERN("M([0-9.]+),([0-9.]+).*L([0-9.]+),([0-9.]+)");
std::regex POLYGON_PATTERN(
    "([0-9.]+) ([0-9.]+) ([0-9.]+) ([0-9.]+) "
    "([0-9.]+) ([0-9.]+)");
} // namespace

using XMLElementPtr = tinyxml2::XMLElement *;
using XMLDocument = tinyxml2::XMLDocument;

EdgesMapper::EdgesMapper(const Graph &graph,
                         const XMLElementPtr root,
                         const SVGNodeMap &nodes_map,
                         SVGEdgeMap &edges_map)
    : graph_{graph},
      root_{root},
      nodes_map_{nodes_map},
      edges_map_{edges_map}
{
  std::ignore = graph_;
  std::ignore = nodes_map_;
}

void EdgesMapper::Map()
{
  if (!root_)
  {
    return;
  }

  for (XMLElementPtr g_element = root_->FirstChildElement(TAG_G); g_element;
       g_element = g_element->NextSiblingElement(TAG_G))
  {
    const auto polygon_element = g_element->FirstChildElement(TAG_POLYGON);
    const auto path_element = g_element->FirstChildElement(TAG_PATH);
    const auto text_element = g_element->FirstChildElement(TAG_TEXT);

    if (polygon_element && path_element && text_element)
    {
      SVGEdge edge_node{g_element, path_element, text_element};
      edges_map_.emplace(std::stoull(text_element->GetText()), edge_node);

      // Remove default arrow stroke
      g_element->DeleteChild(polygon_element);
    }
  }
}
