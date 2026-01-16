#include "src/cpp/image_builder/image_builder.hpp"
#include "src/cpp/image_builder/injectors/content/content_injector.hpp"
#include "src/cpp/image_builder/mapper/mapper.hpp"
#include "src/cpp/image_builder/mapper/svg_graph.hpp"
#include <iostream>
#include <unordered_map>

std::string ImageBuilder::GenerateImage(const std::string &edge_bends,
                                        const Graph &graph,
                                        const std::shared_ptr<ILayout> layout,
                                        const Config &config)
{
  const auto svg_sceleton = layout->GenerateSVG(config);

  SVGGraph svg_graph(svg_sceleton, graph);
  Mapper mapper(svg_graph);
  mapper.Map();
  ContentInjector ie(svg_graph, edge_bends);

  ie.Inject();
  return ie.ToString();
}
