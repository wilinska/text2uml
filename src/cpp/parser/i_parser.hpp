#ifndef SRC_CPP_PARSER_I_PARSER_HPP
#define SRC_CPP_PARSER_I_PARSER_HPP

#include "src/cpp/graph/graph.hpp"
#include <memory>
#include <string>

class IParser
{
public:
  virtual ~IParser() = default;

  virtual Graph Parse(const std::string &input,
                      const bool enable_output = false) = 0;
};

using ParserPtr = std::shared_ptr<IParser>;

#endif // SRC_CPP_PARSER_I_PARSER_HPP
