#ifndef SRC_CPP_PARSER_PLANTUML_CLASS_DIAGRAM_PARSER_HPP
#define SRC_CPP_PARSER_PLANTUML_CLASS_DIAGRAM_PARSER_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/parser/i_parser.hpp"
#include "src/cpp/parser/plantuml/class_diagram/generated_parser/generated_parser.hpp"
#include <iostream>
#include <stack>

namespace class_diagram
{

class Logs
{
public:
  using Token = class_diagram::generated_parser::Token;
  using TokenType = class_diagram::generated_parser::TokenType;

  Logs(std::stack<Token> logs) : logs_(logs) {}

  void push(TokenType type, std::string value)
  {
    logs_.push(Token{type, value});
  }

  Token pop(TokenType type, const bool enable_output)
  {
    const auto token = logs_.top();
    logs_.pop();

    if (enable_output)
    {
      std::cout << "[DEBUG_LOG] Logs: " << type << " " << token.name << "\n";
    }

    if (token.type != type)
    {
      std::cerr << "[DEBUG_LOG] Expected " << type << " instead got "
                << token.type << " " << token.name << "\n";
      return {};
    }

    return token;
  }

  void pop() { logs_.pop(); }
  bool empty() { return logs_.empty(); }
  Token top() { return logs_.top(); }

  std::stack<Token> logs_;
};

class GeneratedParser : public IParser
{
public:
  using Token = class_diagram::generated_parser::Token;
  using TokenType = class_diagram::generated_parser::TokenType;

  GeneratedParser() = default;

  Graph Parse(const std::string &input,
              const bool enable_output = false) override;

private:
  void HandleNewNode(Logs &logs,
                     std::stack<Node> &nodes,
                     const std::string &name,
                     const bool enable_output);

  void HandleNewConnectionWithLeftHead(Logs &logs,
                                       std::stack<Edge> &edges,
                                       std::stack<Node> &nodes,
                                       const std::string &left_arrow_type,
                                       std::size_t &unique_label_id,
                                       const bool enable_output);

  void HandleNewConnection(Logs &logs,
                           std::stack<Edge> &edges,
                           std::stack<Node> &nodes,
                           const std::string &line_type,
                           std::size_t &unique_label_id,
                           const bool enable_output,
                           const std::string &left_arrow_type = "");

  std::string HandleNewNodeMethod(Logs &logs,
                                  const std::string &method_name,
                                  const bool enable_output);

  std::string RemoveCRLF(const std::string &input);
};

} // namespace class_diagram

#endif // SRC_CPP_PARSER_PLANTUML_CLASS_DIAGRAM_PARSER_HPP
