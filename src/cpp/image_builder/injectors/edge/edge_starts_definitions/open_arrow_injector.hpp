#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_OPEN_ARROW_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_OPEN_ARROW_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include "tinyxml2.h"

class EdgeStartOpenArrowInjector : public IInjector
{
public:
  EdgeStartOpenArrowInjector(tinyxml2::XMLDocument &doc) : doc_(doc) {}

  void Inject()
  {
    using namespace tinyxml2;
    XMLElement *defs = doc_.NewElement("defs");
    XMLElement *marker = doc_.NewElement("marker");
    XMLElement *path = doc_.NewElement("path");

    marker->SetAttribute("id", "StartOpenArrow");
    marker->SetAttribute("markerWidth", "10");
    marker->SetAttribute("markerHeight", "10");
    marker->SetAttribute("refX", "2");
    marker->SetAttribute("refY", "5");
    marker->SetAttribute("orient", "auto");
    marker->SetAttribute("markerUnits", "strokeWidth");

    path->SetAttribute("d", "M8,5 L8,1 L0,5 L8,9 z");
    path->SetAttribute("fill", "#fff");
    path->SetAttribute("stroke", "#000");

    doc_.RootElement()->InsertEndChild(defs);
    defs->InsertEndChild(marker);
    marker->InsertEndChild(path);
  }

private:
  tinyxml2::XMLDocument &doc_;
};

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_OPEN_ARROW_INJECTOR_HPP
