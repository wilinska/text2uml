#include "src/cpp/parser/decorators/graphical_parser.hpp"
#include "src/cpp/utils/text/utils.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace
{
constexpr std::uint8_t kWidthMargin{11U};
constexpr std::uint8_t kHeightLineMargin{6U};

// clang-format off
static const std::unordered_map<char, double> PIXEL_WIDTH_ARIAL_12_MAP = {
    // Big letters
    {'A', 7}, {'B', 7}, {'C', 7}, {'D', 7}, {'E', 6}, {'F', 6}, {'G', 7},
    {'H', 7}, {'I', 3}, {'J', 6}, {'K', 7}, {'L', 6}, {'M', 8}, {'N', 7},
    {'O', 7}, {'P', 7}, {'Q', 7}, {'R', 7}, {'S', 6}, {'T', 7}, {'U', 7},
    {'V', 7}, {'W', 8}, {'X', 7}, {'Y', 7}, {'Z', 7},

    // Small letters
    {'a', 6}, {'b', 7}, {'c', 6}, {'d', 7}, {'e', 6}, {'f', 4}, {'g', 7},
    {'h', 7}, {'i', 3}, {'j', 3}, {'k', 6}, {'l', 3}, {'m', 8}, {'n', 7},
    {'o', 7}, {'p', 7}, {'q', 7}, {'r', 5}, {'s', 6}, {'t', 5}, {'u', 7},
    {'v', 7}, {'w', 8}, {'x', 7}, {'y', 7}, {'z', 6},

    // Digits
    {'0', 6}, {'1', 6}, {'2', 6}, {'3', 6}, {'4', 6}, {'5', 6}, {'6', 6},
    {'7', 6}, {'8', 6}, {'9', 6},

    // Specials signs
    {' ', 3}, {'.', 2}, {',', 2}, {'!', 2}, {'?', 6}, {'-', 4}, {'+', 6},
    {'=', 6}, {'@', 10}, {'#', 8}, {'$', 7}, {'%', 10}, {'&', 8}, {'*', 6},
    {'(', 4}, {')', 4}, {'[', 4}, {']', 4}, {'{', 4}, {'}', 4}, {';', 3},
    {':', 3}, {'"', 4}, {'\'', 2}, {'<', 6}, {'>', 6}, {'/', 6}, {'\\', 6},
};
// clang-format on

double Calculate(std::string text)
{
  double result{0};
  std::for_each(text.begin(),
                text.end(),
                [&result](const char c)
                { result += PIXEL_WIDTH_ARIAL_12_MAP.at(c); });
  return result;
}

} // namespace

GraphicalParser::GraphicalParser(const ParserPtr &decorated_parser)
    : decorated_parser_{decorated_parser}
{
}

Graph GraphicalParser::Parse(const std::string &input, const bool enable_output)
{
  auto graph = decorated_parser_->Parse(input, enable_output);
  return AddGraphics(graph);
}

Graph GraphicalParser::AddGraphics(Graph &graph)
{
  for (auto &pair : graph.nodes)
  {
    auto &node = pair.second;
    AddGraphicsToNode(node);
  }
  return graph;
}

void GraphicalParser::AddGraphicsToNode(Node &node)
{
  const double LINE_HEIGHT = (node.attrs.size() == 0) &&
                                     (node.attributes.size() == 0) &&
                                     (node.methods.size() == 0)
                                 ? 7
                                 : 10;
  const auto label = node.type == NodeTypeEnum::Label
                         ? utils::text::removePrefix(node.label)
                         : node.label;

  double width = Calculate(label);
  double height = LINE_HEIGHT;

  if (node.type != NodeTypeEnum::Label)
  {
    const auto margins_width = 10;
    const auto circle_with_label_width = 18;
    width += margins_width;
    width += circle_with_label_width;
    height += 11;
  }
  else
  {
    height += 5;
  }

  if (node.attrs.size() > 0)
  {
    height += node.attrs.size() * (LINE_HEIGHT + kHeightLineMargin) +
              kHeightLineMargin;
  }
  if (node.attributes.size() > 0)
  {
    height += node.attributes.size() * (LINE_HEIGHT + kHeightLineMargin) +
              kHeightLineMargin;
  }
  if (node.methods.size() > 0)
  {
    height += node.methods.size() * (LINE_HEIGHT + kHeightLineMargin) +
              kHeightLineMargin;
  }

  for (const auto &attr : node.attributes)
  {
    width = std::max(width, Calculate(attr.c_str()));
  }

  for (const auto &attr : node.attrs)
  {
    width = std::max(width,
                     Calculate((attr.second + " " + attr.first).c_str()) +
                         kWidthMargin);
  }

  for (const auto &method : node.methods)
  {
    width = std::max(width, Calculate(method.c_str()) + kWidthMargin);
  }

  node.graphics["w"] = std::to_string(width).c_str();
  node.graphics["h"] = std::to_string(height).c_str();
}
