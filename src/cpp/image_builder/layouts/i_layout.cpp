#include "src/cpp/image_builder/layouts/i_layout.hpp"
#include "src/cpp/config/config.hpp"
#include "src/cpp/graph/graph.hpp"
#include <iostream>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/fileformats/GraphIO.h>
#include <sstream>
#include <string>

ILayout::ILayout(Graph &graph)
    : graph{graph},
      G{},
      GA{G,
         ogdf::GraphAttributes::nodeGraphics |
             ogdf::GraphAttributes::edgeGraphics |
             ogdf::GraphAttributes::nodeLabel |
             ogdf::GraphAttributes::edgeStyle |
             ogdf::GraphAttributes::edgeType |
             ogdf::GraphAttributes::edgeArrow |
             ogdf::GraphAttributes::edgeLabel}
{
  for (const auto &node_with_label : graph.nodes)
  {
    if (node_with_label.second.swimlane.has_value())
    {
      swimlane_map = ogdf::NodeArray<std::string>();
    }
  }

  if (swimlane_map.has_value())
  {
    swimlane_placeholder_node = G.newNode();
    GA.label(swimlane_placeholder_node.value()) = "SWIMLANE_PLACEHOLDER_NODE";
  }
  bool first = true;

  for (const auto &pair : graph.nodes)
  {
    const auto &abstract_node = pair.second;

    if (abstract_node.ignore)
    {
      // skipped_nodes.push(abstract_node);
      graph.skipped_nodes_order.push_back(pair.first);
      GA.label(swimlane_placeholder_node.value()) = "SWIMLANE_PLACEHOLDER";
    }

    ogdf::node v = G.newNode();
    id_to_node_map[abstract_node.id] = v;
    if (swimlane_placeholder_node.has_value() && first && abstract_node.id == 0)
    {
      auto ogdfEdge = G.newEdge(swimlane_placeholder_node.value(), v);
      GA.label(ogdfEdge) = "SWIMLANE_PLACEHOLDER_EDGE";
      first = false;
    }

    GA.label(v) = std::to_string(abstract_node.id);
    if (abstract_node.graphics.find("w") != abstract_node.graphics.end())
    {
      GA.width(v) = std::stod(abstract_node.graphics.at("w"));
    }
    if (abstract_node.graphics.find("h") != abstract_node.graphics.end())
    {
      GA.height(v) = std::stod(abstract_node.graphics.at("h"));
    }

    if (swimlane_map.has_value() && abstract_node.swimlane.has_value())
    {
      swimlane_map.value()[v] = abstract_node.swimlane.value();
    }

    switch (abstract_node.activity_enum_type)
    {
    case ActivityTypeEnum::Start:
    case ActivityTypeEnum::Stop: GA.shape(v) = ogdf::Shape::Ellipse; break;
    case ActivityTypeEnum::Conditional:
      GA.shape(v) = ogdf::Shape::Hexagon;
      break;
    case ActivityTypeEnum::EndMerge: GA.shape(v) = ogdf::Shape::Rhomb; break;
    default: GA.shape(v) = ogdf::Shape::Rect; break;
    }

    if (abstract_node.activity_enum_type == ActivityTypeEnum::Fork ||
        abstract_node.activity_enum_type == ActivityTypeEnum::EndFork)
    {
      GA.width(v) = 400;
      GA.height(v) = 5;
    }
  }

  for (const auto &edge : graph.edges)
  {
    if (id_to_node_map.find(std::stoi(edge.source)) == id_to_node_map.end() ||
        id_to_node_map.find(std::stoi(edge.target)) == id_to_node_map.end() ||
        edge.skipping)
    {
      graph.skipped_edges.push_back(edge);
      continue;
    }

    auto src = id_to_node_map[std::stoi(edge.source)];
    auto tgt = id_to_node_map[std::stoi(edge.target)];

    auto ogdfEdge = G.newEdge(src, tgt);

    GA.label(ogdfEdge) = std::to_string(edge.id);
  }
}

std::string ILayout::GenerateSVG(const Config &config)
{
  ApplyLayout(config);

  if (swimlane_map.has_value() && swimlane_placeholder_node.has_value())
  {
    graph.swimlane_start_y = GA.y(swimlane_placeholder_node.value());
  }
  int skipped_pos{0};
  for (const auto &node_label : graph.skipped_nodes_order)
  {
    const auto &abstract_node = graph.nodes.at(node_label);

    auto v = G.newNode();
    id_to_node_map[abstract_node.id] = v;
    GA.label(v) = std::to_string(abstract_node.id);
    GA.x(v) = skipped_pos;
    GA.y(v) = skipped_pos;
    skipped_pos += 5;
    GA.width(v) = std::stod(abstract_node.graphics.at("w"));
    GA.height(v) = std::stod(abstract_node.graphics.at("h"));

    if (swimlane_map.has_value() && abstract_node.swimlane.has_value())
    {
      swimlane_map.value()[v] = abstract_node.swimlane.value();
    }

    switch (abstract_node.activity_enum_type)
    {
    case ActivityTypeEnum::Start:
    case ActivityTypeEnum::Stop: GA.shape(v) = ogdf::Shape::Ellipse; break;
    case ActivityTypeEnum::Conditional:
      GA.shape(v) = ogdf::Shape::Hexagon;
      break;
    case ActivityTypeEnum::EndMerge: GA.shape(v) = ogdf::Shape::Rhomb; break;
    default: GA.shape(v) = ogdf::Shape::Rect; break;
    }

    if (abstract_node.activity_enum_type == ActivityTypeEnum::Fork ||
        abstract_node.activity_enum_type == ActivityTypeEnum::EndFork)
    {
      GA.width(v) = 400;
      GA.height(v) = 5;
    }
  }

  for (const auto &edge : graph.skipped_edges)
  {
    auto src = id_to_node_map[std::stoi(edge.source)];
    auto tgt = id_to_node_map[std::stoi(edge.target)];

    auto ogdfEdge = G.newEdge(src, tgt);

    GA.label(ogdfEdge) = std::to_string(edge.id);
  }

  ApplyNodeTransformations(G, GA);

  // Write the layout to an SVG string
  std::ostringstream oss;
  if (ogdf::GraphIO::drawSVG(GA, oss))
  {
    return oss.str();
  }
  else
  {
    std::cerr << "Error writing SVG to string." << std::endl;
    return {};
  }
}

void ILayout::ApplyNodeTransformations(ogdf::Graph &G,
                                       ogdf::GraphAttributes &GA)
{
  for (auto v : G.nodes)
  {
    if (GA.label(v) == "SWIMLANE_PLACEHOLDER_NODE")
    {
      continue;
    }
    if (std::stoi(GA.label(v)))
    {
      if (graph.nodes_order.size() <= std::stoull(GA.label(v)))
      {
        std::cerr << "ActivityDiagramLayout::ApplyLayout: Node index "
                  << GA.label(v) << " out of bounds." << std::endl;
        continue;
      }
    }
    const auto &graph_node =
        graph.nodes.at(graph.nodes_order[std::stoi(GA.label(v))]);

    if (graph_node.position.x.has_value())
    {
      GA.x(v) = graph_node.position.x.value();
      GA.y(v) = graph_node.position.y.value();
    }
    else if (graph_node.position.dx.has_value())
    {
      GA.x(v) += graph_node.position.dx.value();
      GA.y(v) += graph_node.position.dy.value();
    }
  }
}

double ILayout::StringToDouble(const char *str)
{
  char *endptr;
  double result = strtod(str, &endptr);
  if (endptr == str)
  {
    std::cerr << "Error: Cannot convert string to double " << str << std::endl;
    return 0.0;
  }
  return result;
}
