#include "src/cpp/generator.hpp"
#include "src/cpp/config/config.hpp"
#include "src/cpp/image_builder/image_builder.hpp"
#include "src/cpp/image_builder/layouts/layout_builder.hpp"
#include "src/cpp/parser/builders/decorated_parser_builder.hpp"
#include "src/cpp/parser/plantuml/activity_diagram/parser.hpp"
#include "src/cpp/parser/plantuml/class_diagram/parser.hpp"
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace Text2UML
{

std::pair<std::string, bool>
GenerateClassDiagram(const std::string &uml_text,
                     const std::string &layout_type,
                     const std::string &edge_type,
                     const std::string &config_json)
{
  auto graph = DecoratedParserBuilder{}
                   .Create<class_diagram::GeneratedParser>()
                   .WithGraphics()
                   .Get()
                   ->Parse(uml_text, false);

  LayoutBuilder lb;

  std::string final_layout_type = layout_type;
  std::string final_edge_type = edge_type;

  if (graph.layout_type.has_value())
  {
    final_layout_type = graph.layout_type.value();
  }

  if (graph.edge_type.has_value())
  {
    final_edge_type = graph.edge_type.value();
  }

  const auto layout =
      lb.Create(LayoutTypeStringToEnum(final_layout_type), graph);

  ImageBuilder ib;
  const auto diagram_img =
      ib.GenerateImage(final_edge_type, graph, layout, config_json);

  return std::make_pair(diagram_img, !graph.nodes.empty());
}

std::pair<std::string, bool>
GenerateActivityDiagram(const std::string &uml_text,
                        const std::string &layout_type,
                        const std::string &edge_type,
                        const std::string &config_json)
{
  auto graph = DecoratedParserBuilder{}
                   .Create<activity_diagram::GeneratedParser>()
                   .WithGraphics()
                   .Get()
                   ->Parse(uml_text, false);

  const auto layout = std::make_shared<ActivityDiagramLayout>(graph);

  ImageBuilder ib;
  const auto diagram_img =
      ib.GenerateImage(edge_type, graph, layout, config_json);

  return std::make_pair(diagram_img, !graph.nodes.empty());
}

std::string Generator::Generate(const std::string &uml_text,
                                const std::string &diagram_type,
                                const std::string &layout_type,
                                const std::string &edge_type,
                                const std::string &config_json)
{
  const Config config{config_json};

  if (diagram_type == "activity")
  {
    auto result =
        GenerateActivityDiagram(uml_text, layout_type, edge_type, config_json);
    if (result.second)
    {
      return "activity " + result.first;
    }
  }

  auto class_result =
      GenerateClassDiagram(uml_text, layout_type, edge_type, config_json);
  if (class_result.second)
  {
    return "class " + class_result.first;
  }

  auto result =
      GenerateActivityDiagram(uml_text, layout_type, edge_type, config_json);
  return "activity " + result.first;
}

} // namespace Text2UML
