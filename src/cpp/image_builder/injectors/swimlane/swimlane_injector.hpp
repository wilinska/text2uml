#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_SWIMLANE_SWIMLANE_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_SWIMLANE_SWIMLANE_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/i_injector.hpp"

class SwimlaneInjector : public IInjector
{
public:
  explicit SwimlaneInjector(const Graph &graph,
                            XMLDocument &doc,
                            SVGGraph &svg_graph);
  void Inject();

private:
  const Graph &graph_;

  XMLDocument &doc_;
  SVGGraph &svg_graph_;
};

#endif // SRC_CPP_IMAGE_BUILDER_INJECTORS_SWIMLANE_SWIMLANE_INJECTOR_HPP
