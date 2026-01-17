#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace activity_diagram
{
void GeneratedParser::HandleWhileStatement(
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
                    condition_label.name,
                    ActivityTypeEnum::Conditional,
                    false,
                    enable_output);

  const auto while_node_id = node_parent.value();
  std::optional<std::string> condition_question;
  if (logs.top().type == TokenType::IS)
  {
    logs.pop(TokenType::IS, enable_output);
    condition_question = logs.pop(TokenType::BRACE_CONTENT, enable_output).name;
  }

  HandleNesting(logs,
                graph,
                node_parent,
                condition_question,
                node_id_ctr,
                edge_id_ctr,
                TokenType::WHILE,
                {TokenType::BACKWARD, TokenType::ENDWHILE},
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

  logs.pop(TokenType::ENDWHILE, enable_output);
  std::optional<std::string> backward_label_opt;
  if (logs.top().type == TokenType::BRACE_CONTENT)
  {
    backward_label_opt = logs.pop(TokenType::BRACE_CONTENT, enable_output).name;
  }

  HandleNewEdge(graph,
                node_parent.value(),
                while_node_id,
                edge_id_ctr,
                backward_label_opt,
                true,
                enable_output);

  node_parent = while_node_id;
}
} // namespace activity_diagram
