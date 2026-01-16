#include "src/cpp/parser/builders/decorated_parser_builder.hpp"
#include "src/cpp/parser/decorators/graphical_parser.hpp"

DecoratedParserBuilder &DecoratedParserBuilder::WithGraphics() {
  parser_ = std::make_shared<GraphicalParser>(parser_);
  return *this;
}

ParserPtr DecoratedParserBuilder::Get() const { return parser_; }
