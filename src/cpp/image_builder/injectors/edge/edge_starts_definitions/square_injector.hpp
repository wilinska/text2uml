#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_SQUARE_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_SQUARE_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include "tinyxml2.h"

class EdgeStartSquareInjector : public IInjector
{
public:
  EdgeStartSquareInjector(tinyxml2::XMLDocument &doc) : doc_(doc) {}

  void Inject()
  {
    using namespace tinyxml2;
    XMLElement *defs = doc_.NewElement("defs");
    XMLElement *marker = doc_.NewElement("marker");
    XMLElement *path = doc_.NewElement("path");

    marker->SetAttribute("id", "StartSquare");
    marker->SetAttribute("markerWidth", "10");
    marker->SetAttribute("markerHeight", "10");
    marker->SetAttribute("refX", "1");
    marker->SetAttribute("refY", "5");
    marker->SetAttribute("orient", "auto");
    marker->SetAttribute("markerUnits", "strokeWidth");

    path->SetAttribute("d", "M1,5 L1,1 L9,1 L9,9 L1,9 z");
    path->SetAttribute("fill", "#fff");
    path->SetAttribute("stroke", "#000");

    doc_.RootElement()->InsertEndChild(defs);
    defs->InsertEndChild(marker);
    marker->InsertEndChild(path);
  }

private:
  tinyxml2::XMLDocument &doc_;
};

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_SQUARE_INJECTOR_HPP
