#ifndef SRC_CPP_GRAPH_ENUMS_LINE_TYPE_ENUM_HPP
#define SRC_CPP_GRAPH_ENUMS_LINE_TYPE_ENUM_HPP

#include <cstdint>
#include <ostream>
#include <string>

enum class LineType : std::uint8_t
{
  Solid,
  Dashed
};

inline std::string toString(const LineType value)
{
  switch (value)
  {
  case LineType::Solid: return "Solid";
  case LineType::Dashed: return "Dashed";
  }
  return "Unknown LineType{" +
         std::to_string(static_cast<std::uint8_t>(value)) + "}";
}

inline std::string getStringForEnumValue(const LineType value)
{
  return toString(value);
}

inline std::ostream &operator<<(std::ostream &os, const LineType &value)
{
  os << getStringForEnumValue(value);
  return os;
}

#endif // SRC_CPP_GRAPH_ENUMS_LINE_TYPE_ENUM_HPP
