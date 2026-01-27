#ifndef SRC_CPP_PARSER_PLANTUML_ACTIVITY_DIAGRAM_PARSER_HPP
#define SRC_CPP_PARSER_PLANTUML_ACTIVITY_DIAGRAM_PARSER_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/parser/i_parser.hpp"
#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/generated_parser.hpp"
#include <iostream>
#include <queue>
#include <set>

namespace activity_diagram
{

class Logs
{
public:
  using Token = generated_parser::Token;
  using TokenType = generated_parser::TokenType;

  Logs(std::queue<Token> logs) : logs_(logs) {}

  void push(TokenType type, std::string value)
  {
    logs_.push(Token{type, value});
  }

  Token pop(TokenType type, const bool enable_output)
  {
    const auto token = logs_.front();
    logs_.pop();

    if (enable_output)
    {
      std::cout << "[DEBUG_LOG] Logs: " << type << " " << token.name << "\n";
    }

    if (token.type != type)
    {
      std::cerr << "[DEBUG_LOG] Expected " << type << " instead got "
                << token.type << "\n";
      return {};
    }

    return token;
  }

  void pop() { logs_.pop(); }
  bool empty() { return logs_.empty(); }
  Token top() { return logs_.front(); }

  std::queue<Token> logs_;
};

class GeneratedParser : public IParser
{
public:
  using Token = generated_parser::Token;
  using TokenType = generated_parser::TokenType;

  GeneratedParser() = default;

  Graph Parse(const std::string &input,
              const bool enable_output = false) override;

private:
  void HandleNesting(Logs &logs,
                     Graph &graph,
                     std::optional<std::uint64_t> &node_parent,
                     const std::optional<std::string> &edge_label,
                     std::uint64_t &node_id_ctr,
                     std::uint64_t &edge_id_ctr,
                     std::optional<TokenType> parent_type,
                     std::set<TokenType> end_types,
                     const bool enable_output);

  void HandleNewActivity(Logs &logs,
                         Graph &graph,
                         std::optional<std::uint64_t> &node_parent,
                         const std::optional<std::string> &edge_label,
                         std::uint64_t &node_id_ctr,
                         std::uint64_t &edge_id_ctr,
                         const std::string &label,
                         const ActivityTypeEnum node_type,
                         const bool backward,
                         const bool enable_output);

  void HandleNewEdge(Graph &graph,
                     const std::uint64_t source,
                     const std::uint64_t target,
                     std::uint64_t &edge_id_ctr,
                     std::optional<std::string> label,
                     const bool backward,
                     const bool enable_output);

  void HandleConditionalStatement(Logs &logs,
                                  Graph &graph,
                                  std::optional<std::uint64_t> &node_parent,
                                  const std::optional<std::string> &edge_label,
                                  std::uint64_t &node_id_ctr,
                                  std::uint64_t &edge_id_ctr,
                                  const std::string &label,
                                  const bool enable_output);

  void HandleSwitchStatement(Logs &logs,
                             Graph &graph,
                             std::optional<std::uint64_t> &node_parent,
                             const std::optional<std::string> &edge_label,
                             std::uint64_t &node_id_ctr,
                             std::uint64_t &edge_id_ctr,
                             const std::string &label,
                             const bool enable_output);

  std::optional<std::string>
  HandleWhileStatement(Logs &logs,
                       Graph &graph,
                       std::optional<std::uint64_t> &node_parent,
                       const std::optional<std::string> &edge_label,
                       std::uint64_t &node_id_ctr,
                       std::uint64_t &edge_id_ctr,
                       const std::string &label,
                       const bool enable_output);

  std::optional<std::string>
  HandleRepeatStatement(Logs &logs,
                        Graph &graph,
                        std::optional<std::uint64_t> &node_parent,
                        const std::optional<std::string> &edge_label,
                        std::uint64_t &node_id_ctr,
                        std::uint64_t &edge_id_ctr,
                        const std::string &label,
                        const bool enable_output);

  void HandleForkStatement(Logs &logs,
                           Graph &graph,
                           std::optional<std::uint64_t> &node_parent,
                           const std::optional<std::string> &edge_label,
                           std::uint64_t &node_id_ctr,
                           std::uint64_t &edge_id_ctr,
                           const std::string &label,
                           const bool enable_output);

  void HandleSplitStatement(Logs &logs,
                            Graph &graph,
                            std::optional<std::uint64_t> &node_parent,
                            const std::optional<std::string> &edge_label,
                            std::uint64_t &node_id_ctr,
                            std::uint64_t &edge_id_ctr,
                            const std::string &label,
                            const bool enable_output);

  void HandleGroupStatement(Logs &logs,
                            Graph &graph,
                            std::optional<std::uint64_t> &node_parent,
                            const std::optional<std::string> &edge_label,
                            std::uint64_t &node_id_ctr,
                            std::uint64_t &edge_id_ctr,
                            const std::string &label,
                            const bool enable_output);

  void HandlePartitionStatement(Logs &logs,
                                Graph &graph,
                                std::optional<std::uint64_t> &node_parent,
                                const std::optional<std::string> &edge_label,
                                std::uint64_t &node_id_ctr,
                                std::uint64_t &edge_id_ctr,
                                const std::string &label,
                                const bool enable_output);

  void HandleSwimlaneStatement(Logs &logs,
                               Graph &graph,
                               std::optional<std::uint64_t> &node_parent,
                               const std::optional<std::string> &edge_label,
                               std::uint64_t &node_id_ctr,
                               std::uint64_t &edge_id_ctr,
                               const std::string &label,
                               const bool enable_output);

  std::string RemoveCRLF(const std::string &input);

  std::optional<std::string> current_swim_lane_ = std::nullopt;
};
} // namespace activity_diagram

#endif // SRC_CPP_PARSER_PLANTUML_ACTIVITY_DIAGRAM_PARSER_HPP
