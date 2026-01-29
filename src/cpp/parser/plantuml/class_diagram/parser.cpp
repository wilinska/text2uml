#include "src/cpp/parser/plantuml/class_diagram/parser.hpp"
#include "src/cpp/parser/plantuml/class_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/helpers/helpers.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

namespace
{

/**
 * Formats UML string:
 * - Replaces markers with colored emojis.
 * - Ensures exactly one space after the visibility marker.
 * - Normalizes internal whitespace and trims the string.
 */
std::string FormatUmlString(std::string text)
{
  // 1. Trim leading and trailing whitespace
  text.erase(0, text.find_first_not_of(" \t\r\n"));
  size_t last = text.find_last_not_of(" \t\r\n");
  if (last != std::string::npos)
  {
    text.erase(last + 1);
  }

  if (text.empty())
    return text;

  // 2. Normalize internal whitespace (multiple spaces/tabs -> single space)
  static const std::regex space_regex("[ \t]+");
  text = std::regex_replace(text, space_regex, " ");

  static const std::unordered_set<char> visibility_map = {'-', '#', '~', '+'};

  // 4. Check for visibility marker at the beginning
  auto it = visibility_map.find(text[0]);
  if (it != visibility_map.end())
  {
    std::string symbol = std::string(1, *it);

    // Extract the rest of the string (after the marker)
    std::string rest = text.substr(1);

    // Remove any leading spaces from 'rest' to avoid double spacing
    size_t firstChar = rest.find_first_not_of(" ");
    if (firstChar != std::string::npos)
    {
      rest = rest.substr(firstChar);
    }
    else
    {
      rest = ""; // String was just the marker and spaces
    }

    // Return symbol + forced single space + cleaned rest
    return symbol + " " + rest;
  }

  return text;
}
} // namespace

namespace class_diagram
{
Graph GeneratedParser::Parse(const std::string &input, const bool enable_output)
{
  std::stack<Node> nodes;
  std::stack<Edge> edges;
  std::size_t unique_label_id{0};

  auto logs_pair =
      class_diagram::generated_parser::parse_class_diagram(RemoveCRLF(input));

  Graph graph;
  if (logs_pair.first.size() > 0)
  {
    graph.failed = true;
    graph.failed_string = logs_pair.first;
    return graph;
  }
  auto logs = Logs(logs_pair.second);

  // while (!logs.empty())
  // {
  //   std::cout << "[DEBUG_LOG] GeneratedParser::Parse: Log Type: "
  //             << logs.top().type << "; Name: " << logs.top().name <<
  //             std::endl;
  //   logs.pop();
  // }

  while (!logs.empty())
  {
    const auto token = logs.top();
    logs.pop();

    if (enable_output)
    {
      std::cout << "[DEBUG_LOG] GeneratedParser::parse: Type: " << token.type
                << "; Name: " << token.name << std::endl;
    }

    switch (token.type)
    {
    case TokenType::NODE_NAME:
      HandleNewNode(logs, nodes, token.name, enable_output);
      break;
    case TokenType::ARROW_HEAD:
      HandleNewConnectionWithLeftHead(
          logs, edges, nodes, token.name, unique_label_id, enable_output);
      break;
    case TokenType::LINE:
      HandleNewConnection(
          logs, edges, nodes, token.name, unique_label_id, enable_output);
      break;
    case TokenType::DIAGRAM_TYPE:
      if (!graph.diagram_type.has_value())
      {
        graph.diagram_type = token.name;
        if (enable_output)
        {
          std::cout << "[DEBUG_LOG] GeneratedParser::parse: Diagram type: "
                    << token.name << std::endl;
        }
      }
      break;
    case TokenType::LAYOUT_TYPE:
      if (!graph.layout_type.has_value())
      {
        graph.layout_type = token.name;
        if (enable_output)
        {
          std::cout << "[DEBUG_LOG] GeneratedParser::parse: Layout type: "
                    << token.name << std::endl;
        }
      }
      break;
    case TokenType::EDGE_TYPE:
      if (!graph.edge_type.has_value())
      {
        graph.edge_type = token.name;
        if (enable_output)
        {
          std::cout << "[DEBUG_LOG] GeneratedParser::parse: Edge type: "
                    << token.name << std::endl;
        }
      }
      break;
    default:
      std::cerr << "Expected class name " << token.type << std::endl;
      if (enable_output)
      {
        std::cout << "[DEBUG_LOG] GeneratedParser::parse: Node name: "
                  << token.name << std::endl;
      };
      break;
    }
  }

  std::uint64_t node_id_ctr{0U};
  std::uint64_t edge_id_ctr{0U};

  while (!nodes.empty())
  {
    auto &node = nodes.top();

    if (graph.nodes.find(node.label) == graph.nodes.end())
    {
      node.id = node_id_ctr++;
      graph.nodes_order.push_back(node.label);
      graph.nodes.emplace(node.label, node);
    }
    else
    {
      if (graph.nodes.find(node.label) == graph.nodes.end())
      {
        std::cerr << "Failed to find node " << node.label << " in a map."
                  << std::endl;
        continue;
      }
      auto &saved_node = graph.nodes.at(node.label);

      saved_node.attributes.insert(saved_node.attributes.end(),
                                   node.attributes.begin(),
                                   node.attributes.end());
      saved_node.methods.insert(
          saved_node.methods.end(), node.methods.begin(), node.methods.end());

      if (!saved_node.position.dx.has_value())
      {
        saved_node.position.dx = node.position.dx;
        saved_node.position.dy = node.position.dy;
      }

      if (node.position.x.has_value())
      {
        saved_node.position.x = node.position.x;
        saved_node.position.y = node.position.y;
      }

      saved_node.ignore |= node.ignore;
    }
    nodes.pop();
  }

  while (!edges.empty())
  {
    auto &edge = edges.top();

    edge.id = edge_id_ctr++;
    if (graph.nodes.count(edge.source) != 0)
    {
      if (graph.nodes.find(edge.source) == graph.nodes.end())
      {
        std::cerr << "Failed to find source node " << edge.source
                  << " in a map." << std::endl;
        edges.pop();
        continue;
      }
      const auto source = graph.nodes.at(edge.source);
      edge.source = std::to_string(source.id);
    }

    if (graph.nodes.count(edge.target) != 0)
    {
      if (graph.nodes.find(edge.target) == graph.nodes.end())
      {
        std::cerr << "Failed to find target node " << edge.target
                  << " in a map." << std::endl;
        edges.pop();
        continue;
      }
      const auto target = graph.nodes.at(edge.target);
      edge.target = std::to_string(target.id);
    }

    std::string source = edge.source;
    std::string target = edge.target;
    graph.edges.emplace_back(edge);
    edges.pop();
  }

  return graph;
}

std::string GeneratedParser::HandleNewNodeMethod(Logs &logs,
                                                 const std::string &method_name,
                                                 const bool enable_output)
{
  logs.pop();

  if (logs.top().type != TokenType::METHOD_ARGUMENT)
  {
    return method_name + "()";
  }

  std::stack<std::string> arguments;
  while (!logs.empty() && logs.top().type == TokenType::METHOD_ARGUMENT)
  {
    arguments.push(logs.pop(TokenType::METHOD_ARGUMENT, enable_output).name);
  }

  std::stringstream method_label;

  const auto &first_argument = arguments.top();
  method_label << method_name << "(" << first_argument;
  arguments.pop();

  while (!arguments.empty())
  {
    method_label << ", " << arguments.top();
    arguments.pop();
  }

  method_label << ")";

  return method_label.str();
}

void fillPosition(std::optional<double> &first_value,
                  std::optional<double> &second_value,
                  const std::string &values)
{
  auto [x, y] = extractCoordinates(values);
  first_value = x;
  second_value = y;
  // node.position.dy = dy;
}

void GeneratedParser::HandleNewNode(Logs &logs,
                                    std::stack<Node> &nodes,
                                    const std::string &label,
                                    const bool enable_output)
{
  Node node;
  node.label = label;

  const auto &token = logs.top();

  while (!logs.empty() && logs.top().type != TokenType::NODE_NAME &&
         logs.top().type != TokenType::LINE &&
         logs.top().type != TokenType::NODE_TYPE)

  {
    const auto &token = logs.top();

    switch (token.type)
    {
    case TokenType::ATTRIBUTE:
      node.attributes.push_back(FormatUmlString(token.name));
      logs.pop();
      break;
    case TokenType::METHOD:
      node.methods.push_back(HandleNewNodeMethod(
          logs, FormatUmlString(token.name), enable_output));
      break;
    case TokenType::POSITION:
      fillPosition(node.position.dx, node.position.dy, token.name);
      logs.pop();
      break;
    case TokenType::POSITION_FIXED:
      fillPosition(node.position.x, node.position.y, token.name);
      logs.pop();
      break;
    case TokenType::SKIP_LAYOUT:
      node.ignore = true;
      logs.pop();
      break;
    default: logs.pop(); break;
    }

    if (enable_output)
    {
      std::cout << "[DEBUG_LOG] "
                   "GeneratedParser::HandleNewNode::"
                   "CreateNewNode: "
                   "name: "
                << label << std::endl;
    }
  }

  node.type = node_type::StringToEnum(
      logs.pop(TokenType::NODE_TYPE, enable_output).name);

  std::reverse(node.attributes.begin(), node.attributes.end());
  std::reverse(node.methods.begin(), node.methods.end());

  nodes.push(node);
}

void GeneratedParser::HandleNewConnectionWithLeftHead(
    Logs &logs,
    std::stack<Edge> &edges,
    std::stack<Node> &nodes,
    const std::string &left_arrow_type,
    std::size_t &unique_label_id,
    const bool enable_output)
{
  HandleNewConnection(logs,
                      edges,
                      nodes,
                      logs.pop(TokenType::LINE, enable_output).name,
                      unique_label_id,
                      enable_output,
                      left_arrow_type);
}

void GeneratedParser::HandleNewConnection(Logs &logs,
                                          std::stack<Edge> &edges,
                                          std::stack<Node> &nodes,
                                          const std::string &line_type,
                                          std::size_t &unique_label_id,
                                          const bool enable_output,
                                          const std::string &left_arrow_type)
{
  Node target_node;
  Node source_node;

  bool skipping = false;

  if (logs.top().type == TokenType::SKIP_LAYOUT)
  {
    skipping = true;
    logs.pop(TokenType::SKIP_LAYOUT, enable_output);
  }

  target_node.label = logs.pop(TokenType::NODE_NAME, enable_output).name;
  target_node.type = NodeTypeEnum::Class;
  source_node.label = logs.pop(TokenType::NODE_NAME, enable_output).name;
  source_node.type = NodeTypeEnum::Class;

  nodes.push(target_node);
  nodes.push(source_node);

  if (logs.top().type == TokenType::SKIP_LAYOUT)
  {
    skipping = true;
    logs.pop(TokenType::SKIP_LAYOUT, enable_output);
  }

  bool empty_right_head = false;
  if (logs.top().type == TokenType::LABEL && logs.top().name == "")
  {
    empty_right_head = true;
    logs.pop(TokenType::LABEL, enable_output);
    logs.pop(TokenType::ARROW_HEAD, enable_output);
  }
  if (logs.top().type == TokenType::LABEL)
  {
    const auto label_token = logs.pop(TokenType::LABEL, enable_output);
    if (logs.top().type == TokenType::SPLIT_EDGE)
    {
      Node edge_label_node;
      edge_label_node.label =
          "[L" + std::to_string(unique_label_id++) + "]" + label_token.name;

      edge_label_node.type = NodeTypeEnum::Label;

      Edge after_label_edge;
      Edge before_label_edge;

      after_label_edge.target = target_node.label;
      after_label_edge.source = edge_label_node.label;
      before_label_edge.target = edge_label_node.label;
      before_label_edge.source = source_node.label;

      logs.pop();

      // after_label_edge.right_head =
      //     StringToEnum(logs.pop(TokenType::ARROW_HEAD, enable_output).name);
      after_label_edge.left_head = LineHeadEnum::None;
      before_label_edge.right_head = LineHeadEnum::None;
      // if (left_arrow_type == "")
      // {
      //   before_label_edge.left_head =
      //       StringToEnum(logs.pop(TokenType::ARROW_HEAD,
      //       enable_output).name);
      // }
      // else
      // {
      //   before_label_edge.left_head = LineHeadEnum::None;
      // }

      if (logs.top().type != TokenType::ARROW_HEAD)
      {
        after_label_edge.right_head = LineHeadEnum::None;
        before_label_edge.left_head = LineHeadEnum::None;
      }
      else
      {
        if (left_arrow_type == "")
        {
          if (empty_right_head)
          {
            after_label_edge.right_head = LineHeadEnum::None;
          }
          else
          {
            after_label_edge.right_head = StringToEnum(
                logs.pop(TokenType::ARROW_HEAD, enable_output).name);
          }

          if (logs.top().type == TokenType::LABEL)
          {
            std::cout
                << "Wiemy że będzie label więc się na nią przygotowaliśmy "
                   "na powtorke\n";
            logs.pop();
          }

          before_label_edge.left_head =
              StringToEnum(logs.pop(TokenType::ARROW_HEAD, enable_output).name);
        }
        else
        {
          after_label_edge.right_head =
              StringToEnum(logs.pop(TokenType::ARROW_HEAD, enable_output).name);
          before_label_edge.left_head = LineHeadEnum::None;
        }
      }

      nodes.push(edge_label_node);
      after_label_edge.skipping = skipping;
      before_label_edge.skipping = skipping;
      edges.push(after_label_edge);
      edges.push(before_label_edge);
    }
    else
    {
      Edge edge;
      edge.target = target_node.label;
      edge.source = source_node.label;
      edge.label = label_token.name;
      edge.skipping = skipping;

      if (logs.top().type != TokenType::ARROW_HEAD)
      {
        edge.right_head = LineHeadEnum::None;
        edge.left_head = LineHeadEnum::None;
      }
      else
      {
        if (left_arrow_type == "")
        {
          if (empty_right_head)
          {
            edge.right_head = LineHeadEnum::None;
          }
          else
          {
            if (logs.top().type == TokenType::SKIP_LAYOUT)
            {
              edge.skipping = true;
              logs.pop(TokenType::SKIP_LAYOUT, enable_output);
            }
            edge.right_head = StringToEnum(
                logs.pop(TokenType::ARROW_HEAD, enable_output).name);
          }

          if (logs.top().type == TokenType::LABEL)
          {
            logs.pop();
          }

          if (logs.top().type == TokenType::SKIP_LAYOUT)
          {
            edge.skipping = true;
            logs.pop(TokenType::SKIP_LAYOUT, enable_output);
          }
          edge.left_head =
              StringToEnum(logs.pop(TokenType::ARROW_HEAD, enable_output).name);
        }
        else
        {

          if (logs.top().type == TokenType::SKIP_LAYOUT)
          {
            edge.skipping = true;
            logs.pop(TokenType::SKIP_LAYOUT, enable_output);
          }
          edge.right_head =
              StringToEnum(logs.pop(TokenType::ARROW_HEAD, enable_output).name);
          edge.left_head = LineHeadEnum::None;
        }
      }
      if (logs.top().type == TokenType::SKIP_LAYOUT)
      {
        edge.skipping = true;
        logs.pop(TokenType::SKIP_LAYOUT, enable_output);
      }
      edges.push(edge);
    }
  }
  else
  {
    Edge edge;
    edge.target = target_node.label;
    edge.source = source_node.label;
    edge.skipping = skipping;

    if (left_arrow_type == "")
    {
      if (logs.top().type == TokenType::SKIP_LAYOUT)
      {
        edge.skipping = true;
        logs.pop(TokenType::SKIP_LAYOUT, enable_output);
      }
      edge.right_head =
          StringToEnum(logs.pop(TokenType::ARROW_HEAD, enable_output).name);
      if (logs.top().type == TokenType::SKIP_LAYOUT)
      {
        edge.skipping = true;
        logs.pop(TokenType::SKIP_LAYOUT, enable_output);
      }
      edge.left_head =
          StringToEnum(logs.pop(TokenType::ARROW_HEAD, enable_output).name);
    }
    else
    {
      if (logs.top().type == TokenType::SKIP_LAYOUT)
      {
        edge.skipping = true;
        logs.pop(TokenType::SKIP_LAYOUT, enable_output);
      }
      edge.right_head =
          StringToEnum(logs.pop(TokenType::ARROW_HEAD, enable_output).name);
      edge.left_head = LineHeadEnum::None;
    }
    if (logs.top().type == TokenType::SKIP_LAYOUT)
    {
      edge.skipping = true;
      logs.pop(TokenType::SKIP_LAYOUT, enable_output);
    }
    edges.push(edge);
  }
}

std::string GeneratedParser::RemoveCRLF(const std::string &input)
{
  std::string output;

  for (const auto &c : input)
  {
    if (c != '\r')
    {
      output += c;
    }
  }

  return output;
}
} // namespace class_diagram