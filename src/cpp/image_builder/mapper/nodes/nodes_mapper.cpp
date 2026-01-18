#include "src/cpp/image_builder/mapper/nodes/nodes_mapper.hpp"
#include <iostream>
#include <regex>

NodesMapper::NodesMapper(XMLElementPtr root,
                         std::unordered_map<std::uint64_t, SVGNode> &nodes_map)
    : root_(root),
      nodes_map_(nodes_map)
{
}

void NodesMapper::Map()
{
  for (XMLElementPtr g_element = root_->FirstChildElement(TAG_G); g_element;
       g_element = g_element->NextSiblingElement(TAG_G))
  {
    static constexpr char TAG_TEXT[] = "text";
    static constexpr char TAG_RECT[] = "rect";
    static constexpr char TAG_ELLIPSE[] = "ellipse";

    const XMLElementPtr rect_element = g_element->FirstChildElement(TAG_RECT);
    const XMLElementPtr polygon_element =
        g_element->FirstChildElement(TAG_POLYGON);
    const XMLElementPtr ellipse_element =
        g_element->FirstChildElement(TAG_ELLIPSE);
    const XMLElementPtr text_element = g_element->FirstChildElement(TAG_TEXT);

    if (text_element &&
        text_element->GetText() == std::string("SWIMLANE_PLACEHOLDER_NODE"))
    {
      if (rect_element)
      {
        g_element->DeleteChild(rect_element);
      }
      if (ellipse_element)
      {
        g_element->DeleteChild(ellipse_element);
      }
      if (polygon_element)
      {
        g_element->DeleteChild(polygon_element);
      }
      g_element->DeleteChild(text_element);
      continue;
    }

    if (rect_element && text_element)
    {
      SVGNode svg_node{g_element, rect_element, text_element};

      nodes_map_.emplace(std::stoull(text_element->GetText()), svg_node);
    }
    else if (polygon_element && text_element)
    {
      SVGNode svg_node{g_element, polygon_element, text_element};

      nodes_map_.emplace(std::stoull(text_element->GetText()), svg_node);
    }
    else if (ellipse_element && text_element)
    {
      SVGNode svg_node{g_element, ellipse_element, text_element};

      nodes_map_.emplace(std::stoull(text_element->GetText()), svg_node);
    }
  }
}
