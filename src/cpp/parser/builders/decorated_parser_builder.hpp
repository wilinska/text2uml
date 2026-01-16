#ifndef SRC_CPP_PARSER_BUILDERS_DECORATED_PARSER_BUILDER_HPP
#define SRC_CPP_PARSER_BUILDERS_DECORATED_PARSER_BUILDER_HPP

#include "src/cpp/parser/i_parser.hpp"

class DecoratedParserBuilder
{
public:
  DecoratedParserBuilder &WithGraphics();

  ParserPtr Get() const;

  template <typename ParserT, typename... Args>
  DecoratedParserBuilder &Create(Args &&...args)
  {
    parser_ = std::make_shared<ParserT>(std::forward<Args>(args)...);
    return *this;
  }

private:
  ParserPtr parser_;
};

#endif // SRC_CPP_PARSER_BUILDERS_DECORATED_PARSER_BUILDER_HPP
