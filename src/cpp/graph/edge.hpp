#ifndef SRC_CPP_GRAPH_EDGE_HPP
#define SRC_CPP_GRAPH_EDGE_HPP

#include "src/cpp/graph/enums/line_head_enum.hpp"
#include "src/cpp/graph/enums/line_type_enum.hpp"
#include "src/cpp/graph/object.hpp"
#include <optional>
#include <ostream>

class Edge : public Object
{
public:
  Edge() = default;

  Edge(std::uint64_t id,
       std::map<std::string, std::string> graphics,
       std::map<std::string, std::string> attributes,
       std::string source,
       std::string target,
       std::string type,
       LineHeadEnum left_head,
       LineHeadEnum right_head,
       LineType line_type,
       std::optional<std::string> label)
      : Object(id, graphics, attributes),
        source(source),
        target(target),
        type(type),
        left_head(left_head),
        right_head(right_head),
        line_type(line_type),
        label(label)
  {
  }

  Edge(std::uint64_t id,
       std::map<std::string, std::string> graphics,
       std::map<std::string, std::string> attributes,
       std::string source,
       std::string target,
       std::string type,
       LineHeadEnum left_head,
       LineHeadEnum right_head,
       LineType line_type,
       std::optional<std::string> label,
       bool skipping)
      : Object(id, graphics, attributes),
        source(source),
        target(target),
        type(type),
        left_head(left_head),
        right_head(right_head),
        line_type(line_type),
        label(label),
        skipping(skipping)
  {
  }

  ~Edge() override = default;

  friend std::ostream &operator<<(std::ostream &os, const Edge &node)
  {
    os << "Edge " << node.source << "->" << node.target << " id: " << node.id
       << "\n";
    return os;
  }

  std::string source;
  std::string target;
  std::string type;

  LineHeadEnum left_head;
  LineHeadEnum right_head;

  LineType line_type;

  std::optional<std::string> label;

  bool skipping = false;
  bool backward;
};

#endif // SRC_CPP_GRAPH_EDGE_HPP
