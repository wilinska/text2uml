#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace activity_diagram
{
void GeneratedParser::HandleSplitStatement(
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
                    ActivityTypeEnum::Fork,
                    false,
                    enable_output);

  const auto split_node_id = node_parent.value();

  // then
  HandleNesting(logs,
                graph,
                node_parent,
                std::nullopt,
                node_id_ctr,
                edge_id_ctr,
                TokenType::WHILE,
                {TokenType::END_SPLIT, TokenType::SPLIT_AGAIN},
                enable_output);

  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    std::nullopt,
                    node_id_ctr,
                    edge_id_ctr,
                    "",
                    ActivityTypeEnum::EndSplit,
                    false,
                    enable_output);

  const auto endsplit_node_id = node_parent.value();

  while (logs.top().type == TokenType::SPLIT_AGAIN)
  {
    logs.pop(TokenType::SPLIT_AGAIN, enable_output);

    node_parent = split_node_id;
    HandleNesting(logs,
                  graph,
                  node_parent,
                  std::nullopt,
                  node_id_ctr,
                  edge_id_ctr,
                  TokenType::WHILE,
                  {TokenType::END_SPLIT, TokenType::SPLIT_AGAIN},
                  enable_output);

    HandleNewEdge(graph,
                  node_parent.value(),
                  endsplit_node_id,
                  edge_id_ctr,
                  {},
                  false,
                  enable_output);
  }

  logs.pop(TokenType::END_SPLIT, enable_output);

  node_parent = endsplit_node_id;
}
} // namespace activity_diagram
