#include "src/cpp/image_builder/injectors/content/content_injector.hpp"
#include <iostream>

ContentInjector::ContentInjector(SVGGraph &svg_graph,
                                 const std::string &edge_bends)
    : svg_graph_{svg_graph},
      doc_{svg_graph_.GetDocument()},
      graph_{svg_graph_.graph_},
      node_injector_{graph_, doc_, svg_graph_},
      edge_injector_{doc_, svg_graph_},
      swimlane_injector_{graph_, doc_, svg_graph_},
      edge_bends_{edge_bends}
{
}

void ContentInjector::Inject()
{
  for (auto edge : graph_.edges)
  {
    if (graph_.nodes_order.size() <= std::stoul(edge.source))
    {
      std::cerr << "ContentInjector::Inject: Source node index " << edge.source
                << " out of bounds." << std::endl;
      continue;
    }
    if (graph_.nodes_order.size() <= std::stoul(edge.target))
    {
      std::cerr << "ContentInjector::Inject: Target node index " << edge.target
                << " out of bounds." << std::endl;
      continue;
    }
    if (graph_.nodes.find(graph_.nodes_order.at(std::stoi(edge.source))) ==
        graph_.nodes.end())
    {
      std::cerr << "ContentInjector::Inject: Source node "
                << graph_.nodes_order.at(std::stoi(edge.source))
                << " not found in graph nodes." << std::endl;
      continue;
    }
    if (graph_.nodes.find(graph_.nodes_order.at(std::stoi(edge.target))) ==
        graph_.nodes.end())
    {
      std::cerr << "ContentInjector::Inject: Target node "
                << graph_.nodes_order.at(std::stoi(edge.target))
                << " not found in graph nodes." << std::endl;
      continue;
    }
    edge_injector_.Inject(
        edge,
        edge_bends_,
        graph_.nodes.at(graph_.nodes_order.at(std::stoi(edge.source))),
        graph_.nodes.at(graph_.nodes_order.at(std::stoi(edge.target))));
  }

  edge_injector_.InjectLineEndDefinitions();
  edge_injector_.InjectLineStartsDefinitions();

  for (auto pair : graph_.nodes)
  {
    const auto &node = pair.second;
    node_injector_.Inject(node);
  }

  swimlane_injector_.Inject();
}

void ContentInjector::SaveToFile(const std::string &output_file_name)
{
  tinyxml2::XMLPrinter printer;
  doc_.Print(&printer);
  std::string modified_xml = printer.CStr();

  if (doc_.SaveFile(output_file_name.c_str()) != tinyxml2::XML_SUCCESS)
  {
    std::cerr << "Failed to save edited SVG to " << output_file_name << "."
              << std::endl;
  }
}

std::string ContentInjector::ToString()
{
  tinyxml2::XMLPrinter printer;
  doc_.Print(&printer);
  return std::string(printer.CStr());
}
