#include "src/cpp/image_builder/injectors/edge/edge_injector.hpp"
#include "src/cpp/image_builder/injectors/edge/helpers/bezier_helper.hpp"
#include "src/cpp/image_builder/injectors/edge/helpers/path_helper.hpp"

namespace
{
bool isInt(const std::string &str)
{
  if (str.empty())
    return false;
  size_t i = 0;
  if (str[0] == '-')
  {
    i = 1;
  }
  if (i == 0 && !std::isdigit(static_cast<unsigned char>(str[0])))
    return false;
  for (; i < str.length(); ++i)
  {
    if (!std::isdigit(static_cast<unsigned char>(str[i])))
      return false;
  }
  return true;
}
} // namespace

EdgeInjector::EdgeInjector(XMLDocument &doc, SVGGraph &svg_graph)
    : doc_{doc},
      svg_graph_{svg_graph},
      edge_head_injector_{doc},
      used_line_ends_{}
{
}

void EdgeInjector::Inject(const Edge &edge,
                          const std::string &edge_bending_type_str,
                          const Node &source,
                          const Node &target)
{
  if (svg_graph_.edges_map_.find(edge.id) == svg_graph_.edges_map_.end())
  {
    std::cerr << "Failed to find edge " << edge.source << "->" << edge.target
              << " with id: " << edge.id << " in a map." << std::endl;
    return;
  }

  if (svg_graph_.nodes_map_.find(std::stoi(edge.source)) ==
      svg_graph_.nodes_map_.end())
  {
    std::cerr << "Failed to find source node " << edge.source << " in a map."
              << std::endl;
    return;
  }

  auto &svg_edge = svg_graph_.edges_map_.at(edge.id);
  auto &svg_node = svg_graph_.nodes_map_.at(std::stoi(edge.source));
  const auto path = svg_edge.line;
  const auto rect = svg_node.box;

  svg_edge.parent->SetAttribute("data-source", edge.source.c_str());
  svg_edge.parent->SetAttribute("data-target", edge.target.c_str());

  if (!svg_graph_.graph_.activity)
  {
    InjectLineAdjustments(rect, path);
  }

  InjectLineType(edge, path);
  InjectLineEndType(edge, path);
  InjectLineStartType(edge, path);

  if (edge.label.has_value() and !isInt(edge.label.value()))
  {
    svg_edge.text->SetText(edge.label.value().c_str());
  }
  else
  {
    svg_edge.text->SetText("");
  }

  InjectEdgeBendingType(path,
                        EdgeBendingTypeStringToEnum(edge_bending_type_str));
}

void EdgeInjector::InjectLineType(const Edge &edge, const XMLElementPtr path)
{
  if (edge.line_type == LineType::Dashed)
  {
    const std::string line_pattern(SOLID_LENGTH + "," + GAP_LENGTH);
    path->SetAttribute("stroke-dasharray", line_pattern.c_str());
  }
}

void EdgeInjector::InjectLineAdjustments(const XMLElementPtr rect,
                                         const XMLElementPtr path)
{
  const auto updated_d = helpers::svg::path::UpdateToStartOnRectangleBorder(
      std::string(path->Attribute("d")),
      std::stod(rect->Attribute("x")),
      std::stod(rect->Attribute("y")),
      std::stod(rect->Attribute("width")),
      std::stod(rect->Attribute("height")));

  path->SetAttribute("d", updated_d.c_str());
}

void EdgeInjector::InjectLineEndType(const Edge &edge, const XMLElementPtr path)
{
  if (edge.right_head != LineHeadEnum::None)
  {
    InjectLineEnd(path, edge.right_head);
  }
}

void EdgeInjector::InjectLineStartType(const Edge &edge,
                                       const XMLElementPtr path)
{
  if (edge.left_head != LineHeadEnum::None)
  {
    InjectLineStart(path, edge.left_head);
  }
}

void EdgeInjector::InjectLineEnd(const XMLElementPtr path,
                                 const LineHeadEnum line_head)
{
  const auto end_name = "url(#End" + toString(line_head) + ")";
  path->SetAttribute("marker-end", end_name.c_str());
  path->SetAttribute(
      "d",
      helpers::svg::path::Shorten(std::string(path->Attribute("d")), 6)
          .c_str());
  used_line_ends_.insert(line_head);
}

void EdgeInjector::InjectLineStart(const XMLElementPtr path,
                                   const LineHeadEnum line_head)
{
  const auto end_name = "url(#Start" + toString(line_head) + ")";
  path->SetAttribute("marker-start", end_name.c_str());
  path->SetAttribute("d",
                     helpers::svg::path::path_helpers::shortenPath(
                         std::string(path->Attribute("d")), 7, true)
                         .c_str());
  used_line_starts_.insert(line_head);
}

void EdgeInjector::InjectLineEndDefinitions()
{
  edge_head_injector_.Inject(LineHeadEnum::Arrow, false);

  for (auto &used_line_end : used_line_ends_)
  {
    edge_head_injector_.Inject(used_line_end, false);
  }
}

void EdgeInjector::InjectLineStartsDefinitions()
{
  edge_head_injector_.Inject(LineHeadEnum::Arrow, true);

  for (auto &used_line_start : used_line_starts_)
  {
    edge_head_injector_.Inject(used_line_start, true);
  }
}

void EdgeInjector::InjectLineShift(const XMLElementPtr path,
                                   const Node &source,
                                   const Node &target)
{
  if (source.position.x.has_value())
  {
    path->SetAttribute(
        ATTR_D,
        helpers::svg::path::MovePath(std::string(path->Attribute(ATTR_D)),
                                     source.position.x.value(),
                                     source.position.y.value(),
                                     true)
            .c_str());
  }
  if (target.position.x.has_value())
  {
    path->SetAttribute(
        ATTR_D,
        helpers::svg::path::MovePath(std::string(path->Attribute(ATTR_D)),
                                     target.position.x.value(),
                                     target.position.y.value(),
                                     false)
            .c_str());
  }
}

void EdgeInjector::InjectEdgeBendingType(
    const XMLElementPtr path,
    const EdgeBendingType edge_bending_type)
{
  std::string d{path->Attribute(ATTR_D)};

  switch (edge_bending_type)
  {
  case EdgeBendingType::EdgeBendingType_Bends:
    d = helpers::svg::bezier::PolylineToBezier(d);
    break;
  case EdgeBendingType::EdgeBendingType_BendsOnExistingPoints:
    d = helpers::svg::bezier::PolylineToBezierOnExistingPoints(d);
    break;
  default: break;
  }
  path->SetAttribute(ATTR_D, d.c_str());
}