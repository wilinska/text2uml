
#ifndef SRC_CPP_PARSER_PLANTUML_ACTIVITY_DIAGRAM_GENERATED_PARSER_GENERATED_PARSER_HPP
#define SRC_CPP_PARSER_PLANTUML_ACTIVITY_DIAGRAM_GENERATED_PARSER_GENERATED_PARSER_HPP

#include <queue>
#include <string>

namespace generated_parser
{

enum TokenType
{
  START,
  STOP,
  ACTIVITY_CONTENT,
  IF,
  THEN,
  ELSE,
  ELSEIF,
  ENDIF,
  WHILE,
  ENDWHILE,
  SWITCH,
  ENDSWITCH,
  CASE,
  BRACE_CONTENT,
  STANDARD_ACTIVITY,
  THEN_ACTIVITY,
  ELSE_ACTIVITY,
  EDGE_COMMENT,
  END,
  IS,
  ID,
  COLON,
  SEMICOLON,
  ARROW,
  BACKWARD,
  REPEAT,
  NOT,
  DETACH,
  BREAK,
  KILL,
  FORK,
  AGAIN,
  QUOTED_NAME,
  MERGE,
  FORK_AGAIN,
  END_FORK,
  END_MERGE,
  END_SPLIT,
  SPLIT_AGAIN,
  SPLIT,
  GROUP,
  END_GROUP,
  PARTITION,
  OPEN_CURLY_BRACKET,
  CLOSE_CURLY_BRACKET,
  SWIMLANE,
  END_REPEAT
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
  case TokenType::START: return "START";
  case TokenType::STOP: return "STOP";
  case TokenType::ACTIVITY_CONTENT: return "ACTIVITY_CONTENT";
  case TokenType::THEN: return "THEN";
  case TokenType::IF: return "IF";
  case TokenType::ELSE: return "ELSE";
  case TokenType::ELSEIF: return "ELSEIF";
  case TokenType::ENDIF: return "ENDIF";
  case TokenType::WHILE: return "WHILE";
  case TokenType::ENDWHILE: return "ENDWHILE";
  case TokenType::SWITCH: return "SWITCH";
  case TokenType::CASE: return "CASE";
  case TokenType::ENDSWITCH: return "ENDSWITCH";
  case TokenType::BRACE_CONTENT: return "BRACE_CONTENT";
  case TokenType::STANDARD_ACTIVITY: return "STANDARD_ACTIVITY";
  case TokenType::THEN_ACTIVITY: return "THEN_ACTIVITY";
  case TokenType::ELSE_ACTIVITY: return "ELSE_ACTIVITY";
  case TokenType::EDGE_COMMENT: return "EDGE_COMMENT";
  case TokenType::END: return "END";
  case TokenType::IS: return "IS";
  case TokenType::ID: return "ID";
  case TokenType::COLON: return "COLON";
  case TokenType::SEMICOLON: return "SEMICOLON";
  case TokenType::ARROW: return "ARROW";
  case TokenType::BACKWARD: return "BACKWARD";
  case TokenType::REPEAT: return "REPEAT";
  case TokenType::END_REPEAT: return "END_REPEAT";
  case TokenType::NOT: return "NOT";
  case TokenType::DETACH: return "DETACH";
  case TokenType::BREAK: return "BREAK";
  case TokenType::KILL: return "KILL";
  case TokenType::FORK: return "FORK";
  case TokenType::AGAIN: return "AGAIN";
  case TokenType::QUOTED_NAME: return "QUOTED_NAME";
  case TokenType::MERGE: return "MERGE";
  case TokenType::FORK_AGAIN: return "FORK_AGAIN";
  case TokenType::END_FORK: return "END_FORK";
  case TokenType::END_MERGE: return "END_MERGE";
  case TokenType::SPLIT_AGAIN: return "SPLIT_AGAIN";
  case TokenType::END_SPLIT: return "END_SPLIT";
  case TokenType::SPLIT: return "SPLIT";
  case TokenType::GROUP: return "GROUP";
  case TokenType::END_GROUP: return "END_GROUP";
  case TokenType::PARTITION: return "PARTITION";
  case TokenType::OPEN_CURLY_BRACKET: return "OPEN_CURLY_BRACKET";
  case TokenType::CLOSE_CURLY_BRACKET: return "CLOSE_CURLY_BRACKET";
  case TokenType::SWIMLANE: return "SWIMLANE";
  }
  return "Unknown TokenType{}";
}

inline std::ostream &operator<<(std::ostream &os, const TokenType &value)
{
  os << toString(value);
  return os;
}

void AddToken(const TokenType type, const std::string &name);
void ClearLogs();
std::queue<Token> GetLogs();
void FillLastError(std::string error_report);
std::string GetLastError();
std::pair<std::string, std::queue<Token>> parse(const std::string &input);

} // namespace generated_parser

#endif // SRC_CPP_PARSER_PLANTUML_ACTIVITY_DIAGRAM_GENERATED_PARSER_GENERATED_PARSER_HPP
