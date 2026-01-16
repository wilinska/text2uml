#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_EDGE_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/edge/edge_bending_type.hpp"
#include "src/cpp/image_builder/injectors/edge/edge_head_injector.hpp"
#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include <set>

class EdgeInjector : public IInjector
{
public:
  const std::string SOLID_LENGTH = "5";
  const std::string GAP_LENGTH = "5";

  explicit EdgeInjector(XMLDocument &doc, SVGGraph &svg_graph);

  void Inject(const Edge &edge,
              const std::string &edge_bending_type_str,
              const Node &source,
              const Node &target);
  void InjectLineEndDefinitions();
  void InjectLineStartsDefinitions();
  XMLDocument &GetXMLDocument() { return doc_; }

private:
  void InjectLineAdjustments(const XMLElementPtr rect,
                             const XMLElementPtr path);
  void InjectLineType(const Edge &edge, const XMLElementPtr path);
  void InjectLineEndType(const Edge &edge, const XMLElementPtr path);
  void InjectLineStartType(const Edge &edge, const XMLElementPtr path);

  void InjectLineShift(const XMLElementPtr path,
                       const Node &source,
                       const Node &target);

  void InjectLineStart(const XMLElementPtr path, const LineHeadEnum line_head);
  void InjectLineEnd(const XMLElementPtr path, const LineHeadEnum line_head);

  void InjectEdgeBendingType(const XMLElementPtr path,
                             const EdgeBendingType edge_bending_type);

  XMLDocument &doc_;
  SVGGraph &svg_graph_;

  EdgeHeadInjector edge_head_injector_;
  std::set<LineHeadEnum> used_line_ends_;
  std::set<LineHeadEnum> used_line_starts_;
};

#endif
