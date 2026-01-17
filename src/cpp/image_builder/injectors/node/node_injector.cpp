#include "src/cpp/image_builder/injectors/node/node_injector.hpp"
#include "src/cpp/utils/text/utils.hpp"
#include <iostream>
#include <regex>

namespace
{
std::string extractPartBeforeSemicolon(const std::string &input)
{
  std::regex pattern("^:([a-zA-Z0-9 ]+);.*");
  std::smatch matches;

  if (std::regex_search(input, matches, pattern))
  {
    if (matches.size() > 1)
    {
      return matches[1].str();
    }
  }

  std::regex prefix_pattern("<\\d+>$");

  return std::regex_replace(input, prefix_pattern, "");
}
} // namespace

NodeInjector::NodeInjector(const Graph &graph,
                           XMLDocument &doc,
                           SVGGraph &svg_graph)
    : graph_{graph},
      doc_{doc},
      svg_graph_{svg_graph}
{
}

void NodeInjector::Inject(const Node &node)
{

  static constexpr char ATTR_FILL[] = "fill";
  static constexpr char ATTR_Y[] = "y";

  if (svg_graph_.GetNodesMap().find(node.id) == svg_graph_.GetNodesMap().end())
  {
    std::cerr << "Failed to find node " << node.label << " with id: " << node.id
              << " in a map." << std::endl;
    return;
  }

  if (svg_graph_.GetNodesMap().find(node.id) == svg_graph_.GetNodesMap().end())
  {
    std::cerr << "Failed to find node " << node.label << " with id: " << node.id
              << " in a map." << std::endl;
    return;
  }
  const auto svg_node = svg_graph_.GetNodesMap().at(node.id);
  const auto label = node.type == NodeTypeEnum::Label
                         ? utils::text::removePrefix(node.label)
                         : node.label;

  int ctr = 0;
  std::ignore = ctr;
  auto x = StringToDouble(svg_node.text->Attribute(ATTR_X));
  double y;
  double rect_width;

  {
    if (svg_node.box->Name() == TAG_RECT || !graph_.activity)
    {
      y = StringToDouble(svg_node.box->Attribute(ATTR_Y)) + 10;
      rect_width = StringToDouble(svg_node.box->Attribute(ATTR_WIDTH));
    }
    else
    {
      y = StringToDouble(svg_node.text->Attribute(ATTR_Y));
      rect_width = 1;
    }
  }
  if (node.attrs.size() > 0 || node.attributes.size() > 0 ||
      node.methods.size() > 0)
  {
    InjectHeader(node, svg_node, label, x, y);
  }
  else
  {
    InjectHeader(node, svg_node, label, x, y - 1);
  }

  if (svg_node.box->Name() == TAG_RECT || !graph_.activity)
  {
    x = StringToDouble(svg_node.box->Attribute(ATTR_X)) + 10;
  }

  InjectAttributesSection(svg_node.parent, node.attrs, x, y, rect_width);
  InjectAttributesSection(svg_node.parent, node.attributes, x, y, rect_width);
  InjectAttributesSection(svg_node.parent, node.methods, x, y, rect_width);

  if (node.type == NodeTypeEnum::Label)
  {
    svg_node.box->SetAttribute(ATTR_FILL, "none");
    svg_node.box->SetAttribute(ATTR_FILL, "none");
    svg_node.box->SetAttribute(ATTR_STROKE, "none");
  }
  else
  {
    svg_node.box->SetAttribute(ATTR_FILL, "#ffffff");
    svg_node.box->SetAttribute(ATTR_STROKE, "#000000");
  }

  if (node.activity_enum_type == ActivityTypeEnum::Start ||
      node.activity_enum_type == ActivityTypeEnum::Stop)
  {
    svg_node.text->SetText("");
    svg_node.box->SetAttribute(ATTR_RX, svg_node.box->Attribute(ATTR_RY));
    if (node.activity_enum_type == ActivityTypeEnum::Start)
    {
      svg_node.box->SetAttribute(ATTR_FILL, "#000000");
    }
    else
    {
      XMLElementPtr circle_element = doc_.NewElement("circle");

      circle_element->SetAttribute(ATTR_CX, svg_node.box->Attribute(ATTR_CX));
      circle_element->SetAttribute(ATTR_CY, svg_node.box->Attribute(ATTR_CY));
      circle_element->SetAttribute(ATTR_R, "5");
      circle_element->SetAttribute(ATTR_FILL, "#000000");

      svg_node.parent->InsertEndChild(circle_element);
    }
  }
}

void NodeInjector::InjectHeader(const Node &node,
                                const SVGNode &svg_node,
                                const std::string &node_name,
                                const double x,
                                const double y)
{
  if (node.type == NodeTypeEnum::Label)
  {
    svg_node.text->SetAttribute(ATTR_X, std::to_string(x).c_str());
    svg_node.text->SetAttribute(
        ATTR_Y, AddToStringNumber(std::to_string(y), -3).c_str());
  }
  else if (svg_node.box->Name() == TAG_RECT || !graph_.activity)
  {
    XMLElementPtr circle_element = doc_.NewElement("circle");
    XMLElementPtr circle_text_element = doc_.NewElement("text");

    circle_element->SetAttribute(
        ATTR_CX,
        AddToStringNumber(std::string(svg_node.box->Attribute(ATTR_X)), 12)
            .c_str());
    circle_element->SetAttribute(ATTR_CY, std::to_string(y).c_str());
    circle_element->SetAttribute(ATTR_R, "6");
    circle_element->SetAttribute(ATTR_FILL, "#ff69b4");
    circle_element->SetAttribute(ATTR_STROKE, "#000");

    svg_node.parent->InsertEndChild(circle_element);

    circle_text_element->SetAttribute(
        ATTR_X,
        AddToStringNumber(std::string(svg_node.box->Attribute(ATTR_X)), 12)
            .c_str());
    circle_text_element->SetAttribute(ATTR_Y, std::to_string(y).c_str());
    circle_text_element->SetText(toSign(node.type).c_str());

    circle_text_element->SetAttribute(ATTR_TEXT_ANCHOR, "middle");
    circle_text_element->SetAttribute(ATTR_TEXT_ANCHOR, "middle");
    circle_text_element->SetAttribute(ATTR_FONT_WEIGHT, "bold");
    circle_text_element->SetAttribute(ATTR_DOMINANT_BASELINE, "middle");
    circle_text_element->SetAttribute(ATTR_FONT_FAMILY, "Arial");
    circle_text_element->SetAttribute(ATTR_FONT_SIZE, "7");
    circle_text_element->SetAttribute(ATTR_FILL, "#000000");

    svg_node.parent->InsertEndChild(circle_text_element);

    svg_node.text->SetAttribute(
        ATTR_X, AddToStringNumber(std::to_string(x), 6).c_str());
    svg_node.text->SetAttribute(ATTR_Y, std::to_string(y).c_str());
  }

  svg_node.parent->SetAttribute("data-id", std::to_string(node.id).c_str());
  svg_node.text->SetAttribute(ATTR_TEXT_ANCHOR, "middle");
  svg_node.text->SetAttribute(ATTR_DOMINANT_BASELINE, "middle");
  svg_node.text->SetAttribute(ATTR_FONT_FAMILY, "Arial");
  svg_node.text->SetAttribute(ATTR_FONT_SIZE, "10");
  svg_node.text->SetAttribute(ATTR_FILL, "#000000");
  svg_node.text->SetText(extractPartBeforeSemicolon(node_name).c_str());
}

void NodeInjector::InjectAttributes(
    const XMLElementPtr &text_element,
    const std::map<std::string, std::string> &attrs,
    int &ctr)
{
  for (auto attr : attrs)
  {
    InjectLine(text_element, doc_, attr.second + " " + attr.first, ctr++);
  }
}

void NodeInjector::InjectAttributesSection(
    const XMLElementPtr &parent_element,
    const std::map<std::string, std::string> &attrs,
    double &x,
    double &y,
    const double rect_width,
    const bool last)
{
  if (attrs.size() == 0)
  {
    return;
  }

  InjectLine(parent_element, x - 10, x - 10 + rect_width, y);

  for (auto attr : attrs)
  {
    y += line_height_;
    InjectTextLine(parent_element, doc_, attr.second + " " + attr.first, x, y);
  }
}

void NodeInjector::InjectAttributesSection(
    const XMLElementPtr &parent_element,
    const std::vector<std::string> &attrs,
    double &x,
    double &y,
    const double rect_width,

    const bool last)
{
  if (attrs.size() == 0)
  {
    return;
  }

  InjectLine(parent_element, x - 10, x - 10 + rect_width, y);

  for (auto attr : attrs)
  {
    y += line_height_;
    InjectTextLine(parent_element, doc_, attr, x, y);
  }
}

void NodeInjector::InjectLine(const XMLElementPtr &parent_element,
                              const double x1,
                              const double x2,
                              double &y)
{
  XMLElementPtr line_element = doc_.NewElement("line");

  y += 10;

  line_element->SetAttribute(ATTR_X1, std::to_string(x1).c_str());
  line_element->SetAttribute(ATTR_X2, std::to_string(x2).c_str());
  line_element->SetAttribute(ATTR_Y1, std::to_string(y).c_str());
  line_element->SetAttribute(ATTR_Y2, std::to_string(y).c_str());
  line_element->SetAttribute(ATTR_STROKE, "#000000");
  line_element->SetAttribute(ATTR_STROKE_WIDTH, "1");

  y += 1;

  parent_element->InsertEndChild(line_element);
}

void NodeInjector::InjectAttributes(const XMLElementPtr &text_element,
                                    const std::vector<std::string> &attrs,
                                    int &ctr)
{
  for (auto attr : attrs)
  {
    InjectLine(text_element, doc_, attr, ctr++);
  }
}

void NodeInjector::InjectLine(XMLElementPtr textElement,
                              XMLDocument &doc,
                              const std::string &text,
                              uint16_t line_number)
{

  static constexpr char ATTR_DY[] = "dy";
  static constexpr char EM[] = "em";

  XMLElementPtr line = doc.NewElement("tspan");
  line->SetText(text.c_str());
  line->SetAttribute("x", textElement->Attribute("x"));
  textElement->InsertEndChild(line);
  if (line_number != 0)
  {
    line->SetAttribute(ATTR_DY, (std::to_string(line_height_) + EM).c_str());
  }
}

void NodeInjector::InjectTextLine(XMLElementPtr parent_element,
                                  XMLDocument &doc,
                                  const std::string &text,
                                  const double x,
                                  const double y)
{
  XMLElementPtr text_element = doc.NewElement("text");

  text_element->SetAttribute(ATTR_X, std::to_string(x).c_str());
  text_element->SetAttribute(ATTR_Y, std::to_string(y).c_str());
  text_element->SetAttribute(ATTR_TEXT_ANCHOR, "start");
  text_element->SetAttribute(ATTR_DOMINANT_BASELINE, "middle");
  text_element->SetAttribute(ATTR_FONT_FAMILY, "Arial");
  text_element->SetAttribute(ATTR_FONT_SIZE, "10");
  text_element->SetAttribute(ATTR_FILL, "#000000");
  text_element->SetText(text.c_str());

  parent_element->InsertEndChild(text_element);
}
