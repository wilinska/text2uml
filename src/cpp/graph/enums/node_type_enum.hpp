#ifndef SRC_CPP_GRAPH_ENUMS_NODE_TYPE_ENUM_HPP
#define SRC_CPP_GRAPH_ENUMS_NODE_TYPE_ENUM_HPP

#include <cstdint>
#include <ostream>
#include <string>
#include <unordered_map>

enum class NodeTypeEnum : std::uint8_t
{
  Class,
  Abstract,
  Annotation,
  Circle,
  Diamond,
  Entity,
  Enum,
  Exception,
  Interface,
  Metaclass,
  Protocol,
  Stereotype,
  Struct,
  Label,
  None
};

namespace node_type
{
const static std::string kClass = "Class";
const static std::string kAbstract = "Abstract";
const static std::string kAnnotation = "Annotation";
const static std::string kCircle = "Circle";
const static std::string kDiamond = "Diamond";
const static std::string kEntity = "Entity";
const static std::string kEnum = "Enum";
const static std::string kException = "Exception";
const static std::string kInterface = "Interface";
const static std::string kMetaclass = "Metaclass";
const static std::string kProtocol = "Protocol";
const static std::string kStereotype = "Stereotype";
const static std::string kStruct = "Struct";
const static std::string kLabel = "Label";
const static std::string kNone = "None";

static const std::unordered_map<std::string, NodeTypeEnum>
    stringToNodeTypeEnumMap{{kClass, NodeTypeEnum::Class},
                            {kAbstract, NodeTypeEnum::Abstract},
                            {kAnnotation, NodeTypeEnum::Annotation},
                            {kCircle, NodeTypeEnum::Circle},
                            {kDiamond, NodeTypeEnum::Diamond},
                            {kEntity, NodeTypeEnum::Entity},
                            {kEnum, NodeTypeEnum::Enum},
                            {kException, NodeTypeEnum::Exception},
                            {kInterface, NodeTypeEnum::Interface},
                            {kMetaclass, NodeTypeEnum::Metaclass},
                            {kProtocol, NodeTypeEnum::Protocol},
                            {kStereotype, NodeTypeEnum::Stereotype},
                            {kStruct, NodeTypeEnum::Struct},
                            {kLabel, NodeTypeEnum::Label},
                            {kNone, NodeTypeEnum::None}};

inline NodeTypeEnum StringToEnum(const std::string &str)
{
  const auto it = stringToNodeTypeEnumMap.find(str);
  if (it != stringToNodeTypeEnumMap.end())
  {
    return it->second;
  }
  return NodeTypeEnum::None;
}
} // namespace node_type

inline std::string toString(const NodeTypeEnum value)
{
  switch (value)
  {
  case NodeTypeEnum::Class: return node_type::kClass;
  case NodeTypeEnum::Abstract: return node_type::kAbstract;
  case NodeTypeEnum::Annotation: return node_type::kAnnotation;
  case NodeTypeEnum::Circle: return node_type::kCircle;
  case NodeTypeEnum::Diamond: return node_type::kDiamond;
  case NodeTypeEnum::Entity: return node_type::kEntity;
  case NodeTypeEnum::Enum: return node_type::kEnum;
  case NodeTypeEnum::Exception: return node_type::kException;
  case NodeTypeEnum::Interface: return node_type::kInterface;
  case NodeTypeEnum::Metaclass: return node_type::kMetaclass;
  case NodeTypeEnum::Protocol: return node_type::kProtocol;
  case NodeTypeEnum::Stereotype: return node_type::kStereotype;
  case NodeTypeEnum::Struct: return node_type::kStruct;
  case NodeTypeEnum::Label: return node_type::kLabel;
  case NodeTypeEnum::None: return node_type::kNone;
  }
  return "Unknown LineNodeTypeEnumType{" +
         std::to_string(static_cast<std::uint8_t>(value)) + "}";
}

inline std::string toSign(const NodeTypeEnum value)
{
  switch (value)
  {
  case NodeTypeEnum::Class: return "C";
  case NodeTypeEnum::Abstract: return "A";
  case NodeTypeEnum::Annotation: return "@";
  case NodeTypeEnum::Circle: return "C";
  case NodeTypeEnum::Diamond: return "D";
  case NodeTypeEnum::Entity: return "E";
  case NodeTypeEnum::Enum: return "E";
  case NodeTypeEnum::Exception: return "X";
  case NodeTypeEnum::Interface: return "I";
  case NodeTypeEnum::Metaclass: return "M";
  case NodeTypeEnum::Protocol: return "P";
  case NodeTypeEnum::Stereotype: return "S";
  case NodeTypeEnum::Struct: return "S";
  case NodeTypeEnum::Label: return "L";
  case NodeTypeEnum::None: return "N";
  }
  return "?";
}

inline std::string getStringForEnumValue(const NodeTypeEnum value)
{
  return toString(value);
}

inline std::ostream &operator<<(std::ostream &os, const NodeTypeEnum &value)
{
  os << getStringForEnumValue(value);
  return os;
}

#endif // SRC_CPP_GRAPH_ENUMS_NODE_TYPE_ENUM_HPP
