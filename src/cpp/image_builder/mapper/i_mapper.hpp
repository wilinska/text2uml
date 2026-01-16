#ifndef SRC_CPP_IMAGE_BUILDER_MAPPER_I_MAPPER_HPP
#define SRC_CPP_IMAGE_BUILDER_MAPPER_I_MAPPER_HPP

#include "src/cpp/image_builder/mapper/svg_graph.hpp"

class IMapper
{
public:
  using XMLElementPtr = tinyxml2::XMLElement *;
  using XMLDocument = tinyxml2::XMLDocument;

  using Id = std::uint64_t;
  using SVGNodeMap = std::unordered_map<Id, SVGNode>;
  using SVGEdgeMap = std::unordered_map<Id, SVGEdge>;

  static constexpr char ATTR_D[] = "d";
  static constexpr char ATTR_DY[] = "dy";
  static constexpr char ATTR_HEIGHT[] = "height";
  static constexpr char ATTR_POINTS[] = "points";
  static constexpr char ATTR_WIDTH[] = "width";
  static constexpr char ATTR_X[] = "x";
  static constexpr char ATTR_Y[] = "y";
  static constexpr char TAG_G[] = "g";
  static constexpr char TAG_PATH[] = "path";
  static constexpr char TAG_POLYGON[] = "polygon";
  static constexpr char TAG_RECT[] = "rect";
  static constexpr char TAG_TEXT[] = "text";
};

#endif // SRC_CPP_IMAGE_BUILDER_MAPPER_I_MAPPER_HPP
