#ifndef SRC_CPP_PARSER_DECORATORS_GRAPHICAL_PARSER_HPP
#define SRC_CPP_PARSER_DECORATORS_GRAPHICAL_PARSER_HPP

#include "src/cpp/parser/i_parser.hpp"

class GraphicalParser : public IParser
{
public:
  GraphicalParser(const ParserPtr &decorated_parser);

  virtual ~GraphicalParser() = default;

  Graph Parse(const std::string &input,
              const bool enable_output = false) override;

private:
  Graph AddGraphics(Graph &graph);
  void AddGraphicsToNode(Node &node);

  ParserPtr decorated_parser_;
};

#endif // SRC_CPP_PARSER_DECORATORS_GRAPHICAL_PARSER_HPP
