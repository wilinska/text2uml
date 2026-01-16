#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_ENDS_DEFINITIONS_ARROW_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_ENDS_DEFINITIONS_ARROW_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include "tinyxml2.h"

class EdgeEndArrowInjector : public IInjector
{
public:
  EdgeEndArrowInjector(XMLDocument &doc) : doc_(doc) {}

  void Inject()
  {
    XMLElementPtr defs = doc_.NewElement("defs");
    XMLElementPtr marker = doc_.NewElement("marker");
    XMLElementPtr path = doc_.NewElement("path");

    marker->SetAttribute("id", "EndArrow");
    marker->SetAttribute("markerWidth", "10");
    marker->SetAttribute("markerHeight", "10");
    marker->SetAttribute("refX", "4");
    marker->SetAttribute("refY", "5");
    marker->SetAttribute("orient", "auto");
    marker->SetAttribute("markerUnits", "strokeWidth");

    path->SetAttribute("d", "M4,5 L2,1 L10,5 L2,9 ");
    path->SetAttribute("fill", "#000");

    doc_.RootElement()->InsertEndChild(defs);
    defs->InsertEndChild(marker);
    marker->InsertEndChild(path);
  }

private:
  XMLDocument &doc_;
};

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_ENDS_DEFINITIONS_ARROW_INJECTOR_HPP
