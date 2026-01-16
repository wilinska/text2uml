#include "src/cpp/image_builder/injectors/swimlane/swimlane_injector.hpp"
#include "src/cpp/utils/text/utils.hpp"
#include "tinyxml2.h"
#include <iostream>

namespace
{
std::string removeFirstAndLast(const std::string &str)
{
  if (str.length() <= 2)
  {
    return "";
  }
  return str.substr(1, str.length() - 2);
}
} // namespace

SwimlaneInjector::SwimlaneInjector(const Graph &graph,
                                   XMLDocument &doc,
                                   SVGGraph &svg_graph)
    : graph_{graph},
      doc_{doc},
      svg_graph_{svg_graph}
{
  std::ignore = svg_graph_;
}

void SwimlaneInjector::Inject()
{
  if (graph_.swimlanes.empty())
  {
    return;
  }

  auto *svg = doc_.FirstChildElement("svg");
  if (!svg)
  {
    std::cerr << "Brak elementu <svg>" << std::endl;
    return;
  }

  const char *viewBox = svg->Attribute("viewBox");
  if (viewBox)
  {
    double minX, minY, width, height;
    sscanf(viewBox, "%lf %lf %lf %lf", &minX, &minY, &width, &height);

    char newViewBox[100];
    snprintf(newViewBox,
             sizeof(newViewBox),
             "%f %f %f %f",
             minX - 60,
             minY - 10,
             width + 200,
             height + 40);
    svg->SetAttribute("viewBox", newViewBox);
  }
  else
  {
    svg->SetAttribute("viewBox", "0 0 400 200");
  }

  for (const auto &swimlane : graph_.swimlanes)
  {
    XMLElementPtr rect_element = doc_.NewElement("rect");
    rect_element->SetAttribute(ATTR_X,
                               std::to_string(swimlane.second.x - 10).c_str());
    rect_element->SetAttribute(ATTR_Y, std::to_string(graph_.y).c_str());
    rect_element->SetAttribute(ATTR_WIDTH,
                               std::to_string(swimlane.second.width).c_str());
    rect_element->SetAttribute(ATTR_HEIGHT, std::to_string(30).c_str());
    rect_element->SetAttribute(ATTR_FILL, "#ffffff");
    rect_element->SetAttribute(ATTR_STROKE, "#000000");

    XMLElementPtr box_element = doc_.NewElement("rect");
    box_element->SetAttribute(ATTR_X,
                              std::to_string(swimlane.second.x - 10).c_str());
    box_element->SetAttribute(ATTR_Y, std::to_string(graph_.y).c_str());
    box_element->SetAttribute(ATTR_WIDTH,
                              std::to_string(swimlane.second.width).c_str());
    box_element->SetAttribute(ATTR_HEIGHT,
                              std::to_string(graph_.height + 30).c_str());
    box_element->SetAttribute(ATTR_FILL, "#ffffff");
    box_element->SetAttribute(ATTR_STROKE, "#000000");

    XMLElementPtr text_element = doc_.NewElement("text");
    text_element->SetAttribute(
        ATTR_X,
        std::to_string(swimlane.second.x + swimlane.second.width / 2 - 10)
            .c_str());
    text_element->SetAttribute(ATTR_Y, std::to_string(graph_.y + 18).c_str());
    text_element->SetAttribute(ATTR_TEXT_ANCHOR, "middle");
    text_element->SetAttribute(ATTR_DOMINANT_BASELINE, "start");
    text_element->SetAttribute(ATTR_FONT_FAMILY, "Arial");
    text_element->SetAttribute(ATTR_FONT_SIZE, "12");
    text_element->SetAttribute(ATTR_FILL, "#000000");
    text_element->SetText(removeFirstAndLast(swimlane.second.name).c_str());
    doc_.RootElement()->InsertFirstChild(text_element);
    doc_.RootElement()->InsertFirstChild(rect_element);
    doc_.RootElement()->InsertFirstChild(box_element);
  }
}
