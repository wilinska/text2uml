#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_X_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_X_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include "tinyxml2.h"

class EdgeStartXInjector : public IInjector
{
public:
  EdgeStartXInjector(tinyxml2::XMLDocument &doc) : doc_(doc) {}

  void Inject()
  {
    using namespace tinyxml2;
    XMLElement *defs = doc_.NewElement("defs");
    XMLElement *marker = doc_.NewElement("marker");
    XMLElement *path = doc_.NewElement("path");

    marker->SetAttribute("id", "StartX");
    marker->SetAttribute("markerWidth", "10");
    marker->SetAttribute("markerHeight", "10");
    marker->SetAttribute("refX", "1");
    marker->SetAttribute("refY", "5");
    marker->SetAttribute("orient", "auto");
    marker->SetAttribute("markerUnits", "strokeWidth");

    path->SetAttribute("d", "M1,1 L9,9 M1,9 L9,1");
    path->SetAttribute("stroke", "#000");

    doc_.RootElement()->InsertEndChild(defs);
    defs->InsertEndChild(marker);
    marker->InsertEndChild(path);
  }

private:
  tinyxml2::XMLDocument &doc_;
};

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_STARTS_DEFINITIONS_X_INJECTOR_HPP
