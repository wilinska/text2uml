#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_CONTENT_CONTENT_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_CONTENT_CONTENT_INJECTOR_HPP

#include "src/cpp/graph/graph.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_injector.hpp"
#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include "src/cpp/image_builder/injectors/node/node_injector.hpp"
#include "src/cpp/image_builder/injectors/swimlane/swimlane_injector.hpp"
#include "src/cpp/image_builder/mapper/svg_graph.hpp"
#include <string>
#include <unordered_map>

class ContentInjector : public IInjector
{
public:
  ContentInjector(SVGGraph &svg_graph, const std::string &edge_bends);

  void Inject();
  void SaveToFile(const std::string &output_file_name);
  std::string ToString();

private:
  SVGGraph &svg_graph_;
  XMLDocument &doc_;
  const Graph &graph_;

  NodeInjector node_injector_;
  EdgeInjector edge_injector_;
  SwimlaneInjector swimlane_injector_;

  const std::string &edge_bends_;
};

#endif
