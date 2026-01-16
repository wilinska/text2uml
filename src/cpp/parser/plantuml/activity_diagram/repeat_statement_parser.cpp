#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace activity_diagram
{
void GeneratedParser::HandleRepeatStatement(
    Logs &logs,
    Graph &graph,
    std::optional<std::uint64_t> &node_parent,
    std::uint64_t &node_id_ctr,
    std::uint64_t &edge_id_ctr,
    const std::string &label,
    const bool enable_output)
{

  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    node_id_ctr,
                    edge_id_ctr,
                    "WHILE",
                    ActivityTypeEnum::Repeat,
                    false,
                    enable_output);

  const auto repeat_start_node_id = node_parent.value();

  // then
  HandleNesting(logs,
                graph,
                node_parent,
                node_id_ctr,
                edge_id_ctr,
                TokenType::WHILE,
                {TokenType::BACKWARD, TokenType::REPEAT},
                enable_output);

  if (logs.top().type == TokenType::BACKWARD)
  {
    logs.pop(TokenType::BACKWARD, enable_output);
    const auto backward_token =
        logs.pop(TokenType::ACTIVITY_CONTENT, enable_output);

    HandleNewActivity(logs,
                      graph,
                      node_parent,
                      node_id_ctr,
                      edge_id_ctr,
                      backward_token.name,
                      ActivityTypeEnum::ActivityContent,
                      true,
                      enable_output);
  }

  logs.pop(TokenType::REPEAT, enable_output);

  if (logs.top().type == TokenType::WHILE)
  {
    logs.pop(TokenType::WHILE, enable_output);
    const auto while_token = logs.pop(TokenType::BRACE_CONTENT, enable_output);

    HandleNewActivity(logs,
                      graph,
                      node_parent,
                      node_id_ctr,
                      edge_id_ctr,
                      while_token.name,
                      ActivityTypeEnum::Conditional,
                      false,
                      enable_output);
  }
  // const auto repeat

  HandleNewEdge(graph,
                node_parent.value(),
                repeat_start_node_id,
                edge_id_ctr,
                {},
                true,
                enable_output);

  node_parent = repeat_start_node_id;
}
} // namespace activity_diagram