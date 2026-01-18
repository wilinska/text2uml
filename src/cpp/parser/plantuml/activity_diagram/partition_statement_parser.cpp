#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace activity_diagram
{
void GeneratedParser::HandlePartitionStatement(
    Logs &logs,
    Graph &graph,
    std::optional<std::uint64_t> &node_parent,
    const std::optional<std::string> &edge_label,
    std::uint64_t &node_id_ctr,
    std::uint64_t &edge_id_ctr,
    const std::string &label,
    const bool enable_output)
{
  const auto label_token = logs.pop(TokenType::ID, enable_output);
  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    edge_label,
                    node_id_ctr,
                    edge_id_ctr,
                    "PARTITION" + label_token.name,
                    ActivityTypeEnum::Partition,
                    false,
                    enable_output);

  logs.pop(TokenType::OPEN_CURLY_BRACKET, enable_output);

  HandleNesting(logs,
                graph,
                node_parent,
                std::nullopt,
                node_id_ctr,
                edge_id_ctr,
                TokenType::WHILE,
                {TokenType::CLOSE_CURLY_BRACKET},
                enable_output);

  logs.pop(TokenType::CLOSE_CURLY_BRACKET, enable_output);
  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    std::nullopt,
                    node_id_ctr,
                    edge_id_ctr,
                    "",
                    ActivityTypeEnum::EndPartition,
                    false,
                    enable_output);
}
} // namespace activity_diagram