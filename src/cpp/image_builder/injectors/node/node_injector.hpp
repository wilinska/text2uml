#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_NODE_NODE_INJECTOR_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_NODE_NODE_INJECTOR_HPP

#include "src/cpp/image_builder/injectors/i_injector.hpp"
#include "src/cpp/image_builder/mapper/mapper.hpp"

class NodeInjector : public IInjector
{
public:
  explicit NodeInjector(const Graph &graph,
                        XMLDocument &doc,
                        SVGGraph &svg_graph);

  void Inject(const Node &node);

private:
  void InjectRectangleAttributes(const XMLElementPtr &rect_element);

  void InjectHeader(const Node &node,
                    const SVGNode &svg_node,
                    const std::string &node_name,
                    const double x,
                    const double y);

  void InjectAttributes(const XMLElementPtr &text_element,
                        const std::map<std::string, std::string> &attrs,
                        int &ctr);

  void InjectAttributes(const XMLElementPtr &text_element,
                        const std::vector<std::string> &attrs,
                        int &ctr);

  void InjectLine(XMLElementPtr textElement,
                  XMLDocument &doc,
                  const std::string &text,
                  uint16_t line_number);

  void InjectAttributesSection(const XMLElementPtr &parent_element,
                               const std::map<std::string, std::string> &attrs,
                               double &x,
                               double &y,
                               const double rect_width,
                               const bool last = false);

  void InjectAttributesSection(const XMLElementPtr &parent_element,
                               const std::vector<std::string> &attrs,
                               double &x,
                               double &y,
                               const double rect_width,
                               const bool last = false);

  void InjectTextLine(XMLElementPtr parent_element,
                      XMLDocument &doc,
                      const std::string &text,
                      const double x,
                      const double y);

  void InjectLine(const XMLElementPtr &parent_element,
                  const double x1,
                  const double x2,
                  double &y);

  const Graph &graph_;

  XMLDocument &doc_;
  SVGGraph &svg_graph_;
};

#endif
