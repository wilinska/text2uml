
#ifndef SRC_CPP_PARSER_PLANTUML_CLASS_DIAGRAM_GENERATED_PARSER_GENERATED_PARSER_HPP
#define SRC_CPP_PARSER_PLANTUML_CLASS_DIAGRAM_GENERATED_PARSER_GENERATED_PARSER_HPP

#include <stack>
#include <string>
#include <type_traits>

namespace class_diagram
{
namespace generated_parser
{

enum TokenType
{
  NODE_TYPE,
  NODE_NAME,
  ATTRIBUTE,
  METHOD,
  METHOD_ARGUMENT,
  POSITION,
  POSITION_FIXED,
  SKIP_LAYOUT,
  TYPE,
  CONNECTION,
  LINE,
  ARROW_HEAD,
  LABEL,
  SPLIT_EDGE,
  DIAGRAM_TYPE,
  LAYOUT_TYPE,
  EDGE_TYPE
};

struct Token
{
  TokenType type;
  std::string name;
};

inline std::string toString(const TokenType value)
{
  switch (value)
  {
  case TokenType::NODE_TYPE: return "NODE_TYPE";
  case TokenType::NODE_NAME: return "NODE_NAME";
  case TokenType::ATTRIBUTE: return "ATTRIBUTE";
  case TokenType::METHOD_ARGUMENT: return "METHOD_ARGUMENT";
  case TokenType::METHOD: return "METHOD";
  case TokenType::POSITION: return "POSITION";
  case TokenType::POSITION_FIXED: return "POSITION_FIXED";
  case TokenType::SKIP_LAYOUT: return "SKIP_LAYOUT";
  case TokenType::TYPE: return "TYPE";
  case TokenType::CONNECTION: return "CONNECTION";
  case TokenType::LINE: return "LINE";
  case TokenType::ARROW_HEAD: return "ARROW_HEAD";
  case TokenType::LABEL: return "LABEL";
  case TokenType::SPLIT_EDGE: return "SPLIT_EDGE";
  case TokenType::DIAGRAM_TYPE: return "DIAGRAM_TYPE";
  case TokenType::LAYOUT_TYPE: return "LAYOUT_TYPE";
  case TokenType::EDGE_TYPE: return "EDGE_TYPE";
  }
  return "Unknown TokenType{" + std::to_string(int(value)) + "}";
}

inline std::ostream &operator<<(std::ostream &os, const TokenType &value)
{
  os << toString(value);
  return os;
}
void FillLastError(std::string error_report);
std::string GetLastError();
std::pair<std::string, std::stack<Token>>
parse_class_diagram(const std::string &input);

} // namespace generated_parser
} // namespace class_diagram

#endif // SRC_CPP_PARSER_PLANTUML_CLASS_DIAGRAM_GENERATED_PARSER_GENERATED_PARSER_HPP
