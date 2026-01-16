#ifndef SRC_CPP_GRAPH_GRAPH_HPP
#define SRC_CPP_GRAPH_GRAPH_HPP

#include "src/cpp/graph/edge.hpp"
#include "src/cpp/graph/node.hpp"
#include "src/cpp/graph/swimlane_config.hpp"
#include <map>
#include <unordered_map>
#include <vector>

struct Graph
{
  std::map<std::string, Node> nodes;
  std::vector<std::string> nodes_order;
  std::vector<std::string> skipped_nodes_order;

  std::vector<Edge> edges;
  std::vector<Edge> skipped_edges;

  std::unordered_map<std::string, int> swimlanes_ids;
  std::unordered_map<int, SwimlaneConfig> swimlanes;

  std::optional<std::string> diagram_type;
  std::optional<std::string> layout_type;
  std::optional<std::string> edge_type;
  bool activity = false;

  double height = 0;
  double y = 20;

  friend std::ostream &operator<<(std::ostream &os, const Graph &graph)
  {
    os << "Graph:\n";
    os << "activity: " << graph.activity << "\n";
    os << "Nodes:\n";

    size_t ctr = 0;
    for (auto pair : graph.nodes)
    {
      os << ctr++ << ". " << pair.first << " -> " << pair.second << "\n";
    }
    os << "Nodes order:\n";
    ctr = 0;
    for (auto str : graph.nodes_order)
    {
      os << ctr++ << ". " << str << "\n";
    }
    os << "Edges:\n";
    ctr = 0;
    for (auto edge : graph.edges)
    {
      os << ctr++ << ". " << edge << "\n";
    }
    os << "Graph End\n\n";
    return os;
  }
};

#endif // SRC_CPP_GRAPH_GRAPH_HPP
