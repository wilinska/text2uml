#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/helpers/helpers.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace activity_diagram
{

Graph GeneratedParser::Parse(const std::string &input, const bool enable_output)
{
  Graph graph;

  graph.activity = true;

  std::uint64_t node_id_ctr{0U};
  std::uint64_t edge_id_ctr{0U};
  std::optional<std::uint64_t> node_parent{};

  auto logs_pair = generated_parser::parse(RemoveCRLF(input));
  if (logs_pair.first.size() > 0)
  {
    graph.failed = true;
    graph.failed_string = logs_pair.first;
    return graph;
  }
  auto logs = Logs(logs_pair.second);

  if (!logs.empty() && logs.top().type == TokenType::SWIMLANE)
  {
    current_swim_lane_ = logs.top().name;
  }

  HandleNesting(logs,
                graph,
                node_parent,
                std::nullopt,
                node_id_ctr,
                edge_id_ctr,
                {},
                {},
                enable_output);

  return graph;
}

void GeneratedParser::HandleNesting(
    Logs &logs,
    Graph &graph,
    std::optional<std::uint64_t> &node_parent,
    const std::optional<std::string> &edge_label,
    std::uint64_t &node_id_ctr,
    std::uint64_t &edge_id_ctr,
    std::optional<TokenType> parent_type,
    std::set<TokenType> end_types,
    const bool enable_output)
{
  std::optional<std::string> next_label = edge_label;
  bool reset_label = false;
  while (!logs.empty() && end_types.count(logs.top().type) == 0)
  {
    const auto token = logs.top();
    logs.pop();

    if (enable_output)
    {
      std::cout << "[DEBUG_LOG] ClassDiagramGeneratedParser::parse: Type: "
                << token.type << "; Name: " << token.name << std::endl;
      std::cout << "[DEBUG_LOG] ClassDiagramGeneratedParser::parse: Type: "
                << logs.top().type << "; Name: " << logs.top().name
                << std::endl;
    }
    if (reset_label)
    {
      next_label = std::nullopt;
    }
    else
    {
      reset_label = true;
    }

    switch (token.type)
    {
    case TokenType::START:
      HandleNewActivity(logs,
                        graph,
                        node_parent,
                        next_label,
                        node_id_ctr,
                        edge_id_ctr,
                        "",
                        ActivityTypeEnum::Start,
                        false,
                        enable_output);
      break;
    case TokenType::STOP:
      HandleNewActivity(logs,
                        graph,
                        node_parent,
                        next_label,
                        node_id_ctr,
                        edge_id_ctr,
                        "",
                        ActivityTypeEnum::Stop,
                        false,
                        enable_output);
      break;
    case TokenType::END:
      HandleNewActivity(logs,
                        graph,
                        node_parent,
                        next_label,
                        node_id_ctr,
                        edge_id_ctr,
                        "END",
                        ActivityTypeEnum::End,
                        false,
                        enable_output);
      break;
    case TokenType::BREAK:
      HandleNewActivity(logs,
                        graph,
                        node_parent,
                        next_label,
                        node_id_ctr,
                        edge_id_ctr,
                        "BREAK",
                        ActivityTypeEnum::Break,
                        false,
                        enable_output);
      break;
    case TokenType::DETACH: node_parent = std::nullopt; break;
    case TokenType::ACTIVITY_CONTENT:
      HandleNewActivity(logs,
                        graph,
                        node_parent,
                        next_label,
                        node_id_ctr,
                        edge_id_ctr,
                        token.name,
                        ActivityTypeEnum::ActivityContent,
                        false,
                        enable_output);
      break;
    case TokenType::IF:
      HandleConditionalStatement(logs,
                                 graph,
                                 node_parent,
                                 next_label,
                                 node_id_ctr,
                                 edge_id_ctr,
                                 token.name,
                                 enable_output);
      break;
    case TokenType::SWITCH:
      HandleSwitchStatement(logs,
                            graph,
                            node_parent,
                            next_label,
                            node_id_ctr,
                            edge_id_ctr,
                            token.name,
                            enable_output);
      break;
    case TokenType::WHILE:
      next_label = HandleWhileStatement(logs,
                                        graph,
                                        node_parent,
                                        next_label,
                                        node_id_ctr,
                                        edge_id_ctr,
                                        token.name,
                                        enable_output);
      reset_label = false;
      break;
    case TokenType::REPEAT:
      next_label = HandleRepeatStatement(logs,
                                         graph,
                                         node_parent,
                                         next_label,
                                         node_id_ctr,
                                         edge_id_ctr,
                                         token.name,
                                         enable_output);
      reset_label = false;
      break;
    case TokenType::FORK:
      HandleForkStatement(logs,
                          graph,
                          node_parent,
                          next_label,
                          node_id_ctr,
                          edge_id_ctr,
                          token.name,
                          enable_output);
      break;
    case TokenType::SPLIT:
      HandleSplitStatement(logs,
                           graph,
                           node_parent,
                           next_label,
                           node_id_ctr,
                           edge_id_ctr,
                           token.name,
                           enable_output);
      break;
    case TokenType::GROUP:
      HandleGroupStatement(logs,
                           graph,
                           node_parent,
                           next_label,
                           node_id_ctr,
                           edge_id_ctr,
                           token.name,
                           enable_output);
      break;
    case TokenType::PARTITION:
      HandlePartitionStatement(logs,
                               graph,
                               node_parent,
                               next_label,
                               node_id_ctr,
                               edge_id_ctr,
                               token.name,
                               enable_output);
      break;
    case TokenType::SWIMLANE: current_swim_lane_ = token.name; break;
    default:
      std::cerr << "Expected class name but got" << token.type << std::endl;
      if (enable_output)
      {
        std::cout
            << "[DEBUG_LOG] ClassDiagramGeneratedParser::parse: Node name: "
            << token.name << std::endl;
      };
      break;
    }
  }
}

void GeneratedParser::HandleNewActivity(
    Logs &logs,
    Graph &graph,
    std::optional<std::uint64_t> &node_parent,
    const std::optional<std::string> &edge_label,
    std::uint64_t &node_id_ctr,
    std::uint64_t &edge_id_ctr,
    const std::string &label,
    const ActivityTypeEnum node_type,
    const bool backward,
    const bool enable_output)
{
  Node node;
  node.id = node_id_ctr;
  node.label = label + "<" + std::to_string(node_id_ctr) + ">";
  node.type = NodeTypeEnum::Class;
  node.activity_enum_type = node_type;
  node.swimlane = current_swim_lane_;
  graph.nodes_order.push_back(node.label);
  graph.nodes.emplace(node.label, node);

  if (node_parent.has_value())
  {
    HandleNewEdge(graph,
                  node_parent.value(),
                  node_id_ctr,
                  edge_id_ctr,
                  edge_label,
                  backward,
                  enable_output);
  }
  if (node_type != ActivityTypeEnum::End && node_type != ActivityTypeEnum::Stop)
  {
    node_parent = node_id_ctr;
  }
  else
  {
    node_parent = std::nullopt;
  }
  ++node_id_ctr;
}
void GeneratedParser::HandleNewEdge(Graph &graph,
                                    const std::uint64_t source,
                                    const std::uint64_t target,
                                    std::uint64_t &edge_id_ctr,
                                    std::optional<std::string> label,
                                    const bool backward,
                                    const bool enable_output)
{
  Edge edge;

  edge.id = edge_id_ctr++;
  edge.label = std::to_string(edge.id);
  if (backward)
  {
    edge.target = std::to_string(source);
    edge.source = std::to_string(target);
    edge.right_head = LineHeadEnum::None;
    edge.left_head = LineHeadEnum::Arrow;
    edge.skipping = true;
  }
  else
  {
    edge.target = std::to_string(target);
    edge.source = std::to_string(source);
    edge.right_head = LineHeadEnum::Arrow;
    edge.left_head = LineHeadEnum::None;
  }

  if (label.has_value())
  {
    edge.label = label;
  }

  edge.backward = backward;

  graph.edges.emplace_back(edge_id_ctr,
                           edge.graphics,
                           edge.attributes,
                           edge.source,
                           edge.target,
                           edge.type,
                           edge.left_head,
                           edge.right_head,
                           edge.line_type,
                           edge.label);
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
} // namespace activity_diagram