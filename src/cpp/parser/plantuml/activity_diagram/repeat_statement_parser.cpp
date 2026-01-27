#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace
{
std::string removeOuterParentheses(const std::string &input)
{
  if (input.length() >= 2 && input.front() == '(' && input.back() == ')')
  {
    return input.substr(1, input.length() - 2);
  }
  return input;
}
} // namespace

namespace activity_diagram
{
std::optional<std::string> GeneratedParser::HandleRepeatStatement(
    Logs &logs,
    Graph &graph,
    std::optional<std::uint64_t> &node_parent,
    const std::optional<std::string> &edge_label,
    std::uint64_t &node_id_ctr,
    std::uint64_t &edge_id_ctr,
    const std::string &label,
    const bool enable_output)
{
  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    edge_label,
                    node_id_ctr,
                    edge_id_ctr,
                    "",
                    ActivityTypeEnum::Repeat,
                    false,
                    enable_output);

  const auto repeat_start_node_id = node_parent.value();

  // then
  HandleNesting(logs,
                graph,
                node_parent,
                std::nullopt,
                node_id_ctr,
                edge_id_ctr,
                TokenType::WHILE,
                {TokenType::BACKWARD, TokenType::END_REPEAT},
                enable_output);

  if (logs.top().type == TokenType::BACKWARD)
  {
    logs.pop(TokenType::BACKWARD, enable_output);
    const auto backward_token =
        logs.pop(TokenType::ACTIVITY_CONTENT, enable_output);

    HandleNewActivity(logs,
                      graph,
                      node_parent,
                      std::nullopt,
                      node_id_ctr,
                      edge_id_ctr,
                      backward_token.name,
                      ActivityTypeEnum::ActivityContent,
                      true,
                      enable_output);
  }

  logs.pop(TokenType::END_REPEAT, enable_output);

  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    const auto while_token = removeOuterParentheses(
        logs.pop(TokenType::BRACE_CONTENT, enable_output).name);

    HandleNewActivity(logs,
                      graph,
                      node_parent,
                      std::nullopt,
                      node_id_ctr,
                      edge_id_ctr,
                      while_token,
                      ActivityTypeEnum::Conditional,
                      false,
                      enable_output);
  }

  if (logs.top().type == TokenType::IS)
  {
    logs.pop(TokenType::IS, enable_output);
  }

  std::optional<std::string> condition_yes = std::nullopt;
  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    condition_yes = removeOuterParentheses(
        logs.pop(TokenType::BRACE_CONTENT, enable_output).name);
  }

  HandleNewEdge(graph,
                node_parent.value(),
                repeat_start_node_id,
                edge_id_ctr,
                condition_yes,
                true,
                enable_output);

  if (logs.top().type == TokenType::NOT)
  {
    logs.pop(TokenType::NOT, enable_output);
  }

  std::optional<std::string> condition_no = std::nullopt;
  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    condition_no = removeOuterParentheses(
        logs.pop(TokenType::BRACE_CONTENT, enable_output).name);
  }
  node_parent = repeat_start_node_id;
  return condition_no;
}
} // namespace activity_diagram