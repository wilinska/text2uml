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
void GeneratedParser::HandleConditionalStatement(
    Logs &logs,
    Graph &graph,
    std::optional<std::uint64_t> &node_parent,
    const std::optional<std::string> &edge_label,
    std::uint64_t &node_id_ctr,
    std::uint64_t &edge_id_ctr,
    const std::string &label,
    const bool enable_output)
{
  const auto condition_label =
      logs.pop(TokenType::BRACE_CONTENT, enable_output);

  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    edge_label,
                    node_id_ctr,
                    edge_id_ctr,
                    removeOuterParentheses(condition_label.name),
                    ActivityTypeEnum::Conditional,
                    false,
                    enable_output);

  auto if_node_id = node_parent;
  std::optional<std::string> then_label_opt;

  if (logs.top().type == TokenType::IS)
  {
    logs.pop(TokenType::IS, enable_output);
    then_label_opt = logs.pop(TokenType::BRACE_CONTENT, enable_output).name;
  }
  // then
  logs.pop(TokenType::THEN, enable_output);

  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    then_label_opt = logs.pop(TokenType::BRACE_CONTENT, enable_output).name;
  }

  HandleNesting(logs,
                graph,
                node_parent,
                then_label_opt,
                node_id_ctr,
                edge_id_ctr,
                TokenType::IF,
                {TokenType::ELSE, TokenType::ELSEIF, TokenType::BRACE_CONTENT},
                enable_output);

  // endif node
  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    std::nullopt,
                    node_id_ctr,
                    edge_id_ctr,
                    "",
                    ActivityTypeEnum::EndMerge,
                    false,
                    enable_output);

  const auto endif_node_id = node_parent;

  node_parent = if_node_id;
  std::optional<std::string> else_label_opt;

  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    else_label_opt = logs.pop(TokenType::BRACE_CONTENT, enable_output).name;
  }

  while (logs.top().type == TokenType::ELSEIF)
  { // elseif
    node_parent = if_node_id;
    logs.pop(TokenType::ELSEIF, enable_output);

    const auto elseifcondition_label =
        logs.pop(TokenType::BRACE_CONTENT, enable_output);

    logs.pop(TokenType::THEN, enable_output);

    if (logs.top().type == TokenType::BRACE_CONTENT)
    {
      else_label_opt = logs.pop(TokenType::BRACE_CONTENT, enable_output).name;
    }

    HandleNewActivity(logs,
                      graph,
                      node_parent,
                      std::nullopt,
                      node_id_ctr,
                      edge_id_ctr,
                      removeOuterParentheses(elseifcondition_label.name),
                      ActivityTypeEnum::Conditional,
                      false,
                      enable_output);

    if_node_id = node_parent;

    HandleNesting(
        logs,
        graph,
        node_parent,
        else_label_opt,
        node_id_ctr,
        edge_id_ctr,
        TokenType::ELSEIF,
        {TokenType::ELSE, TokenType::ELSEIF, TokenType::BRACE_CONTENT},
        enable_output);

    std::optional<std::string> endif_label_opt;
    if (logs.top().type == TokenType::BRACE_CONTENT)
    {
      endif_label_opt = logs.pop(TokenType::BRACE_CONTENT, enable_output).name;
    }

    HandleNewEdge(graph,
                  node_parent.value(),
                  endif_node_id.value(),
                  edge_id_ctr,
                  endif_label_opt,
                  false,
                  enable_output);

    node_parent = if_node_id;
  }

  // else
  logs.pop(TokenType::ELSE, enable_output);
  std::optional<std::string> else_final_label_opt;

  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    else_final_label_opt =
        logs.pop(TokenType::BRACE_CONTENT, enable_output).name;
  }

  HandleNesting(logs,
                graph,
                node_parent,
                else_final_label_opt,
                node_id_ctr,
                edge_id_ctr,
                TokenType::IF,
                {TokenType::ENDIF},
                enable_output);

  logs.pop(TokenType::ENDIF, enable_output);

  HandleNewEdge(graph,
                node_parent.value(),
                endif_node_id.value(),
                edge_id_ctr,
                {},
                false,
                enable_output);

  node_parent = endif_node_id;
}
} // namespace activity_diagram
