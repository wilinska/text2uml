#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_ENDS_DEFINITIONS_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_ENDS_DEFINITIONS_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include "tinyxml2.h"

template <LineHeadEnum T> class EdgeEndDefinitionInjector : public IInjector
{
public:
  EdgeEndDefinitionInjector(XMLDocument &doc) : doc_(doc) {}

  void Inject()
  {
    std::cerr << "Injecting edge enum deginition for " << T
              << " is not implemented." << std::endl;
  }

private:
  XMLDocument &doc_;
};

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_ENDS_DEFINITIONS_INJECTOR_HPP
