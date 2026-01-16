#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_CIRCLE_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_CIRCLE_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include "tinyxml2.h"

class EdgeStartCircleInjector : public IInjector
{
public:
  EdgeStartCircleInjector(tinyxml2::XMLDocument &doc) : doc_(doc) {}

  void Inject()
  {
    using namespace tinyxml2;
    XMLElement *defs = doc_.NewElement("defs");
    XMLElement *marker = doc_.NewElement("marker");
    XMLElement *circle = doc_.NewElement("circle");
    XMLElement *line1 = doc_.NewElement("line");
    XMLElement *line2 = doc_.NewElement("line");

    marker->SetAttribute("id", "EndCircle");
    marker->SetAttribute("markerWidth", "10");
    marker->SetAttribute("markerHeight", "10");
    marker->SetAttribute("refX", "8");
    marker->SetAttribute("refY", "5");
    marker->SetAttribute("orient", "auto");
    marker->SetAttribute("fill", "#000");
    marker->SetAttribute("markerUnits", "strokeWidth");

    circle->SetAttribute("cx", "5");
    circle->SetAttribute("cy", "5");
    circle->SetAttribute("r", "4");
    circle->SetAttribute("fill", "#fff");
    circle->SetAttribute("stroke", "#000");

    line1->SetAttribute("x1", "2");
    line1->SetAttribute("y1", "2");
    line1->SetAttribute("x2", "8");
    line1->SetAttribute("y2", "8");
    line1->SetAttribute("stroke", "#000");

    line2->SetAttribute("x1", "2");
    line2->SetAttribute("y1", "8");
    line2->SetAttribute("x2", "8");
    line2->SetAttribute("y2", "2");
    line2->SetAttribute("stroke", "#000");

    doc_.RootElement()->InsertEndChild(defs);
    defs->InsertEndChild(marker);
    marker->InsertEndChild(circle);
    marker->InsertEndChild(line1);
    marker->InsertEndChild(line2);
  }

private:
  tinyxml2::XMLDocument &doc_;
};

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_CIRCLE_INJECTOR_HPP
