#ifndef SRC_CPP_GRAPH_ENUMS_LINE_HEAD_ENUM_HPP
#define SRC_CPP_GRAPH_ENUMS_LINE_HEAD_ENUM_HPP

#include <cstdint>
#include <ostream>
#include <string>
#include <unordered_map>

const static std::string kArrow = "Arrow";
const static std::string kOpenArrow = "OpenArrow";
const static std::string kRhomb = "Rhomb";
const static std::string kOpenRhomb = "OpenRhomb";
const static std::string kSquare = "Square";
const static std::string kCross = "X";
const static std::string kThreeLines = "ThreeLines";
const static std::string kCircle = "Circle";
const static std::string kNone = "None";

enum class LineHeadEnum : std::uint8_t
{
  Arrow,
  OpenArrow,
  Rhomb,
  OpenRhomb,
  Square,
  Cross,
  ThreeLines,
  Circle,
  None
};

static const std::unordered_map<std::string, LineHeadEnum>
    stringToLineHeadEnumMap{{kArrow, LineHeadEnum::Arrow},
                            {kOpenArrow, LineHeadEnum::OpenArrow},
                            {kRhomb, LineHeadEnum::Rhomb},
                            {kOpenRhomb, LineHeadEnum::OpenRhomb},
                            {kSquare, LineHeadEnum::Square},
                            {kCross, LineHeadEnum::Cross},
                            {kThreeLines, LineHeadEnum::ThreeLines},
                            {kCircle, LineHeadEnum::Circle},
                            {kNone, LineHeadEnum::None}};

inline std::string toString(const LineHeadEnum value)
{
  switch (value)
  {
  case LineHeadEnum::Arrow: return kArrow;
  case LineHeadEnum::OpenArrow: return kOpenArrow;
  case LineHeadEnum::Rhomb: return kRhomb;
  case LineHeadEnum::OpenRhomb: return kOpenRhomb;
  case LineHeadEnum::Square: return kSquare;
  case LineHeadEnum::Cross: return kCross;
  case LineHeadEnum::ThreeLines: return kThreeLines;
  case LineHeadEnum::Circle: return kCircle;
  case LineHeadEnum::None: return kNone;
  }
  return "Unknown LineHeadEnum{" +
         std::to_string(static_cast<std::uint8_t>(value)) + "}";
}

inline LineHeadEnum StringToEnum(const std::string &str)
{
  const auto it = stringToLineHeadEnumMap.find(str);
  if (it != stringToLineHeadEnumMap.end())
  {
    return it->second;
  }
  return LineHeadEnum::None;
}

inline std::string getStringForEnumValue(const LineHeadEnum value)
{
  return toString(value);
}

inline std::ostream &operator<<(std::ostream &os, const LineHeadEnum &value)
{
  os << getStringForEnumValue(value);
  return os;
}

#endif // SRC_CPP_GRAPH_ENUMS_LINE_HEAD_ENUM_HPP
