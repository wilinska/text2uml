#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace activity_diagram
{
void GeneratedParser::HandleConditionalStatement(
    Logs &logs,
    Graph &graph,
    std::optional<std::uint64_t> &node_parent,
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
                    node_id_ctr,
                    edge_id_ctr,
                    condition_label.name,
                    ActivityTypeEnum::Conditional,
                    false,
                    enable_output);

  auto if_node_id = node_parent;

  if (logs.top().type == TokenType::IS)
  {
    logs.pop(TokenType::IS, enable_output);
    const auto condition_question =
        logs.pop(TokenType::BRACE_CONTENT, enable_output);
  }
  // then
  logs.pop(TokenType::THEN, enable_output);

  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    const auto then_label = logs.pop(TokenType::BRACE_CONTENT, enable_output);
    std::ignore = then_label;
  }

  HandleNesting(logs,
                graph,
                node_parent,
                node_id_ctr,
                edge_id_ctr,
                TokenType::IF,
                {TokenType::ELSE, TokenType::ELSEIF, TokenType::BRACE_CONTENT},
                enable_output);

  // endif node
  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    node_id_ctr,
                    edge_id_ctr,
                    "",
                    ActivityTypeEnum::EndMerge,
                    false,
                    enable_output);

  const auto endif_node_id = node_parent;

  node_parent = if_node_id;

  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    const auto endif_label = logs.pop(TokenType::BRACE_CONTENT, enable_output);
    std::ignore = endif_label;
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
      const auto endif_label =
          logs.pop(TokenType::BRACE_CONTENT, enable_output);
      std::ignore = endif_label;
    }

    HandleNewActivity(logs,
                      graph,
                      node_parent,
                      node_id_ctr,
                      edge_id_ctr,
                      elseifcondition_label.name,
                      ActivityTypeEnum::Conditional,
                      false,
                      enable_output);

    if_node_id = node_parent;

    HandleNesting(
        logs,
        graph,
        node_parent,
        node_id_ctr,
        edge_id_ctr,
        TokenType::ELSEIF,
        {TokenType::ELSE, TokenType::ELSEIF, TokenType::BRACE_CONTENT},
        enable_output);

    if (logs.top().type == TokenType::BRACE_CONTENT)
    {
      const auto endif_label =
          logs.pop(TokenType::BRACE_CONTENT, enable_output);
      std::ignore = endif_label;
    }

    HandleNewEdge(graph,
                  node_parent.value(),
                  endif_node_id.value(),
                  edge_id_ctr,
                  {},
                  false,
                  enable_output);

    node_parent = if_node_id;
  }

  // else
  logs.pop(TokenType::ELSE, enable_output);

  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    const auto endif_label = logs.pop(TokenType::BRACE_CONTENT, enable_output);
    std::ignore = endif_label;
  }

  HandleNesting(logs,
                graph,
                node_parent,
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
