#ifndef SRC_CPP_GENERATOR_HPP
#define SRC_CPP_GENERATOR_HPP

#include <string>

namespace Text2UML
{
class Generator
{
public:
  static std::string Generate(const std::string &uml_text,
                              const std::string &diagram_type,
                              const std::string &layout_type,
                              const std::string &edge_type,
                              const std::string &config);
};
} // namespace Text2UML

#endif // SRC_CPP_GENERATOR_HPP
