#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace activity_diagram
{
void GeneratedParser::HandleSwitchStatement(
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

  const auto switch_node_id = node_parent;

  // then
  logs.pop(TokenType::CASE, enable_output);
  const auto case_condition_label =
      logs.pop(TokenType::BRACE_CONTENT, enable_output);

  HandleNesting(logs,
                graph,
                node_parent,
                case_condition_label.name,
                node_id_ctr,
                edge_id_ctr,
                TokenType::CASE,
                {TokenType::CASE, TokenType::ENDSWITCH},
                enable_output);

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

  const auto endswitch_node_id = node_parent;

  while (logs.top().type == TokenType::CASE)
  { // elseif
    node_parent = switch_node_id;
    logs.pop(TokenType::CASE, enable_output);

    const auto cont_case_condition_label =
        logs.pop(TokenType::BRACE_CONTENT, enable_output);

    HandleNesting(logs,
                  graph,
                  node_parent,
                  cont_case_condition_label.name,
                  node_id_ctr,
                  edge_id_ctr,
                  TokenType::CASE,
                  {TokenType::CASE, TokenType::ENDSWITCH},
                  enable_output);

    HandleNewEdge(graph,
                  node_parent.value(),
                  endswitch_node_id.value(),
                  edge_id_ctr,
                  {},
                  false,
                  enable_output);
  }

  node_parent = endswitch_node_id;
  logs.pop(TokenType::ENDSWITCH, enable_output);
}
} // namespace activity_diagram
