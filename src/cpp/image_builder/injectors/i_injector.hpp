#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_I_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_I_INJECTOR_HPP

#include "src/cpp/image_builder/mapper/mapper.hpp"
#include <iostream>

class IInjector
{
public:
  static constexpr char EM[] = "em";
  static constexpr char EMPTY[] = "";
  static constexpr char ATTR_D[] = "d";
  static constexpr char ATTR_DY[] = "dy";
  static constexpr char ATTR_HEIGHT[] = "height";
  static constexpr char ATTR_POINTS[] = "points";
  static constexpr char ATTR_WIDTH[] = "width";
  static constexpr char ATTR_X[] = "x";
  static constexpr char ATTR_CX[] = "cx";
  static constexpr char ATTR_X1[] = "x1";
  static constexpr char ATTR_X2[] = "x2";
  static constexpr char ATTR_Y[] = "y";
  static constexpr char ATTR_CY[] = "cy";
  static constexpr char ATTR_Y1[] = "y1";
  static constexpr char ATTR_Y2[] = "y2";
  static constexpr char ATTR_FILL[] = "fill";
  static constexpr char ATTR_R[] = "r";
  static constexpr char ATTR_RX[] = "rx";
  static constexpr char ATTR_RY[] = "ry";
  static constexpr char ATTR_STROKE[] = "stroke";
  static constexpr char ATTR_STROKE_WIDTH[] = "stroke-width";
  static constexpr char ATTR_TEXT_ANCHOR[] = "text-anchor";
  static constexpr char ATTR_DOMINANT_BASELINE[] = "dominant-baseline";
  static constexpr char ATTR_FONT_FAMILY[] = "font-family";
  static constexpr char ATTR_FONT_SIZE[] = "font-size";
  static constexpr char ATTR_FONT_WEIGHT[] = "font-weight";
  static constexpr char TAG_G[] = "g";
  static constexpr char TAG_PATH[] = "path";
  static constexpr char TAG_POLYGON[] = "polygon";
  static constexpr char TAG_RECT[] = "rect";
  static constexpr char TAG_TEXT[] = "text";

  using XMLElementPtr = tinyxml2::XMLElement *;
  using XMLAttributePtr = tinyxml2::XMLAttribute *;
  using XMLDocument = tinyxml2::XMLDocument;

  virtual ~IInjector() {}

  std::string AddToStringNumber(std::string str, int value)
  {
    return std::to_string(std::stoi(std::string(str)) + value);
  }

  double StringToDouble(const char *str)
  {
    char *endptr;
    double result = strtod(str, &endptr);

    if (endptr == str)
    {
      std::cerr << str << std::endl;
      fprintf(stderr, "Error: Cannot convert string to double\n");
      return 0.0;
    }

    return result;
  }

  const uint8_t line_height_temp = 12;
  const uint8_t &line_height_ = line_height_temp;
};

#endif
