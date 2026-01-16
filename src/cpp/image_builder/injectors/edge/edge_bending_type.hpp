#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_BENDING_TYPE_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_BENDING_TYPE_HPP

#include "src/cpp/graph/graph.hpp"
#include <iostream>
#include <sstream>
#include <string>

const static std::string kPolyline = "Polyline";
const static std::string kBends = "BendsNew";
const static std::string kBendsOnExisting = "Bends";

enum class EdgeBendingType
{
  EdgeBendingType_Polyline,
  EdgeBendingType_Bends,
  EdgeBendingType_BendsOnExistingPoints

};

static const std::unordered_map<std::string, EdgeBendingType>
    stringToEdgeBendingTypeMap{
        {kPolyline, EdgeBendingType::EdgeBendingType_Polyline},
        {kBends, EdgeBendingType::EdgeBendingType_Bends},
        {kBendsOnExisting,
         EdgeBendingType::EdgeBendingType_BendsOnExistingPoints}};

inline std::string toString(const EdgeBendingType value)
{
  switch (value)
  {
  case EdgeBendingType::EdgeBendingType_Polyline: return kPolyline;
  case EdgeBendingType::EdgeBendingType_Bends: return kBends;
  case EdgeBendingType::EdgeBendingType_BendsOnExistingPoints:
    return kBendsOnExisting;
  default: return kPolyline;
  }
}

inline EdgeBendingType EdgeBendingTypeStringToEnum(const std::string &str)
{
  const auto it = stringToEdgeBendingTypeMap.find(str);
  if (it != stringToEdgeBendingTypeMap.end())
  {
    return it->second;
  }
  return EdgeBendingType::EdgeBendingType_Polyline;
}

inline std::string getStringForEnumValue(const EdgeBendingType value)
{
  return toString(value);
}

inline std::ostream &operator<<(std::ostream &os, const EdgeBendingType &value)
{
  os << getStringForEnumValue(value);
  return os;
}

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_BENDING_TYPE_HPP
