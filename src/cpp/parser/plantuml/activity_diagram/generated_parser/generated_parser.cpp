
#include "src/cpp/parser/plantuml/activity_diagram/generated_parser/generated_parser.hpp"
#include <iostream>
#include <queue>
#include <string>

namespace generated_parser
{
std::queue<Token> logs;

void ClearLogs()
{
  std::queue<Token> empty;
  logs.swap(empty);
}

void AddToken(const TokenType type, const std::string &name)
{
  Token token;
  token.type = type;
  token.name = name;
  logs.emplace(token);
}

std::queue<Token> GetLogs() { return logs; }

} // namespace generated_parser
