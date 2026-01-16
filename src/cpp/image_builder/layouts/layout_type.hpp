#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_LAYOUT_TYPE_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_LAYOUT_TYPE_HPP

// #include <fstream>
// #include <iostream>
// #include <ogdf/fileformats/GraphIO.h>
#include "src/cpp/graph/graph.hpp"
#include <iostream>
#include <sstream>
#include <string>

const static std::string kCircular = "Circular";
const static std::string kFMMM = "FMMM";
const static std::string kOptimalHierarchy = "OptimalHierarchy";
const static std::string kOrthogonal = "Orthogonal";
const static std::string kSugiyama = "Sugiyama";
const static std::string kTree = "Tree";

enum class LayoutType
{
  LayoutType_Circular,
  LayoutType_FMMM,
  LayoutType_OptimalHierarchy,
  LayoutType_Orthogonal,
  LayoutType_Sugiyama,
  LayoutType_Tree,
  // LayoutType_Sugiyama,

};

static const std::unordered_map<std::string, LayoutType> stringToLayoutTypeMap{
    {kCircular, LayoutType::LayoutType_Circular},
    {kFMMM, LayoutType::LayoutType_FMMM},
    {kOptimalHierarchy, LayoutType::LayoutType_OptimalHierarchy},
    {kOrthogonal, LayoutType::LayoutType_Orthogonal},
    {kSugiyama, LayoutType::LayoutType_Sugiyama},
    {kTree, LayoutType::LayoutType_Tree} //,
    // {kThreeLines, LayoutType::ThreeLines},
    // {kCircle, LayoutType::Circle},
    // {kNone, LayoutType::None}
};

inline std::string toString(const LayoutType value)
{
  switch (value)
  {
  case LayoutType::LayoutType_Circular: return kCircular;
  case LayoutType::LayoutType_FMMM: return kFMMM;
  case LayoutType::LayoutType_OptimalHierarchy: return kOptimalHierarchy;
  case LayoutType::LayoutType_Orthogonal: return kOrthogonal;
  case LayoutType::LayoutType_Tree: return kTree;
  case LayoutType::LayoutType_Sugiyama: return kSugiyama;
  default: return kOptimalHierarchy;
  }
}

inline LayoutType LayoutTypeStringToEnum(const std::string &str)
{
  const auto it = stringToLayoutTypeMap.find(str);
  if (it != stringToLayoutTypeMap.end())
  {
    return it->second;
  }
  return LayoutType::LayoutType_Orthogonal;
}

inline std::string getStringForEnumValue(const LayoutType value)
{
  return toString(value);
}

inline std::ostream &operator<<(std::ostream &os, const LayoutType &value)
{
  os << getStringForEnumValue(value);
  return os;
}

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_LAYOUT_TYPE_HPP
