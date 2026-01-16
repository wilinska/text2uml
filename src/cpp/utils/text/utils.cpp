#include "src/cpp/utils/text/utils.hpp"
#include <regex>
#include <string>

namespace utils
{
namespace text
{

std::string removePrefix(const std::string &input)
{
  // Regex to match [L<number>]
  std::regex prefixPattern(R"(\[L\d+\]\s*)");

  // Replace the prefix with an empty string
  return std::regex_replace(input, prefixPattern, "");
}

} // namespace text
} // namespace utils
