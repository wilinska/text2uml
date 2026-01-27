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
    std::cerr << "SVG element not found" << std::endl;
    return;
  }

  // Calculate total width based on the rightmost swimlane
  double totalWidth = 0;
  for (const auto &pair : graph_.swimlanes)
  {
    totalWidth = std::max(totalWidth, pair.second.x + pair.second.width);
  }

  // Adjust ViewBox to accommodate the new swimlane layout
  // We add a small margin (e.g., 20px) for better visibility
  const char *viewBox = svg->Attribute("viewBox");
  double minX, minY, vbWidth, vbHeight;
  if (viewBox &&
      sscanf(viewBox, "%lf %lf %lf %lf", &minX, &minY, &vbWidth, &vbHeight) ==
          4)
  {
    char newViewBox[128];
    snprintf(newViewBox,
             sizeof(newViewBox),
             "%f %f %f %f",
             -20.0, // Start slightly before 0
             minY - 10,
             totalWidth + 40, // Total width + margins
             vbHeight + 60);
    svg->SetAttribute("viewBox", newViewBox);
  }

  auto y_double = graph_.swimlane_start_y.has_value()
                      ? graph_.swimlane_start_y.value()
                      : 0.0; // Default to top if not set

  auto y_str = std::to_string(y_double);
  const double headerHeight = 30.0;

  // Iterate through swimlanes and create SVG elements
  for (const auto &pair : graph_.swimlanes)
  {
    const auto &swimlane = pair.second;

    // 1. Create the full vertical lane box (background)
    XMLElementPtr box_element = doc_.NewElement("rect");
    box_element->SetAttribute("x", std::to_string(swimlane.x).c_str());
    box_element->SetAttribute("y", y_str.c_str());
    box_element->SetAttribute("width", std::to_string(swimlane.width).c_str());
    // Height covers the header + total graph height
    box_element->SetAttribute(
        "height", std::to_string(graph_.height + headerHeight).c_str());
    box_element->SetAttribute("fill", "#ffffff");
    box_element->SetAttribute("stroke", "#000000");
    box_element->SetAttribute("stroke-width", "1");

    // 2. Create the header rectangle (title area)
    XMLElementPtr rect_element = doc_.NewElement("rect");
    rect_element->SetAttribute("x", std::to_string(swimlane.x).c_str());
    rect_element->SetAttribute("y", y_str.c_str());
    rect_element->SetAttribute("width", std::to_string(swimlane.width).c_str());
    rect_element->SetAttribute("height", std::to_string(headerHeight).c_str());
    rect_element->SetAttribute("fill", "#f4f4f4"); // Light grey for header
    rect_element->SetAttribute("stroke", "#000000");

    // 3. Create the text label
    XMLElementPtr text_element = doc_.NewElement("text");
    double centerX = swimlane.x + (swimlane.width / 2.0);
    text_element->SetAttribute("x", std::to_string(centerX).c_str());
    text_element->SetAttribute(
        "y", std::to_string(y_double + (headerHeight / 2.0) + 4.0).c_str());
    text_element->SetAttribute("text-anchor", "middle");
    text_element->SetAttribute("font-family", "Arial");
    text_element->SetAttribute("font-size", "12");
    text_element->SetAttribute("font-weight", "bold");
    text_element->SetAttribute("fill", "#000000");
    text_element->SetText(removeFirstAndLast(swimlane.name).c_str());

    // Insert elements at the beginning of the SVG so they are rendered as the
    // background layer Order of insertion matters: Last inserted via
    // InsertFirstChild becomes the first in XML
    doc_.RootElement()->InsertFirstChild(
        text_element); // Topmost of the background
    doc_.RootElement()->InsertFirstChild(rect_element); // Middle
    doc_.RootElement()->InsertFirstChild(box_element);  // Bottom
  }
}
