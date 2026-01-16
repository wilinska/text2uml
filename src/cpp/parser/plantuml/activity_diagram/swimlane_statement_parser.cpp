#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/parser.tab.h"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace activity_diagram
{
void GeneratedParser::HandleSwimlaneStatement(
    Logs &logs,
    Graph &graph,
    std::optional<std::uint64_t> &node_parent,
    std::uint64_t &node_id_ctr,
    std::uint64_t &edge_id_ctr,
    const std::string &label,
    const bool enable_output)
{

  std::string swim_name = label.substr(1, label.size() - 2);
  HandleNewActivity(logs,
                    graph,
                    node_parent,
                    node_id_ctr,
                    edge_id_ctr,
                    "SWIMLANE " + swim_name,
                    ActivityTypeEnum::Swimlane,
                    false,
                    enable_output);
}
} // namespace activity_diagram
