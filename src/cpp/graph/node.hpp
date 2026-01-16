#ifndef SRC_CPP_GRAPH_NODE_HPP
#define SRC_CPP_GRAPH_NODE_HPP

#include "src/cpp/graph/enums/activity_type_enum.hpp"
#include "src/cpp/graph/enums/node_type_enum.hpp"
#include "src/cpp/graph/object.hpp"
#include <optional>
#include <vector>

struct Position
{
  std::optional<double> x;
  std::optional<double> y;
  std::optional<double> dx;
  std::optional<double> dy;
};

class Node : public Object
{
public:
  Node() = default;
  ~Node() override = default;

  friend std::ostream &operator<<(std::ostream &os, const Node &node)
  {
    os << "Node " << node.label << " id: " << node.id << "{\n";
    os << "Attrs:\n";
    size_t ctr = 0;
    for (auto pair : node.attrs)
    {
      os << ctr++ << ". " << pair.first << " -> " << pair.second << "\n";
    }
    os << "Attributes:\n";
    ctr = 0;
    for (auto str : node.attributes)
    {
      os << ctr++ << ". " << str << "\n";
    }
    os << "Methods:\n";
    ctr = 0;
    for (auto str : node.methods)
    {
      os << ctr++ << ". " << str << "\n";
    }
    os << "}\n";
    return os;
  }

  bool is_label = false;
  bool ignore = false;
  std::string label;

  NodeTypeEnum type{NodeTypeEnum::None};
  ActivityTypeEnum activity_enum_type{ActivityTypeEnum::None};

  std::optional<int> rank{};
  std::optional<std::string> swimlane = std::nullopt;

  Position position;

  std::map<std::string, std::string> attrs;
  std::vector<std::string> attributes;
  std::vector<std::string> methods;
};

#endif // SRC_CPP_GRAPH_NODE_HPP
