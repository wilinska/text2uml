#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_LAYOUT_BUILDER_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_LAYOUT_BUILDER_HPP

#include "src/cpp/image_builder/layouts/activity_diagram_layout/activity_diagram_layout.hpp"
#include "src/cpp/image_builder/layouts/circular_layout/circular_layout.hpp"
#include "src/cpp/image_builder/layouts/fmmm_layout/fmmm_layout.hpp"
#include "src/cpp/image_builder/layouts/i_layout.hpp"
#include "src/cpp/image_builder/layouts/layout_type.hpp"
#include "src/cpp/image_builder/layouts/optimal_hierarchy_layout/optimal_hierarchy_layout.hpp"
#include "src/cpp/image_builder/layouts/orthogonal_layout/orthogonal_layout.hpp"
#include "src/cpp/image_builder/layouts/sugiyama_layout/sugiyama_layout.hpp"
#include "src/cpp/image_builder/layouts/tree_layout/tree_layout.hpp"
#include <memory>

class LayoutBuilder
{
public:
  // Metoda do tworzenia layoutu na podstawie typu
  std::shared_ptr<ILayout> Create(LayoutType type, Graph &graph)
  {
    switch (type)
    {
    case LayoutType::LayoutType_Circular:
      return std::make_shared<CircularGraphLayout>(graph);
    case LayoutType::LayoutType_FMMM:
      return std::make_shared<FMMMGraphLayout>(graph);
    case LayoutType::LayoutType_OptimalHierarchy:
      return std::make_shared<OptimalHierarchyGraphLayout>(graph);
    case LayoutType::LayoutType_Orthogonal:
      return std::make_shared<OrthogonalGraphLayout>(graph);
    case LayoutType::LayoutType_Sugiyama:
      return std::make_shared<SugiyamaGraphLayout>(graph);
    case LayoutType::LayoutType_Tree:
      return std::make_shared<TreeGraphLayout>(graph);
    default: return std::make_shared<ActivityDiagramLayout>(graph);
    }
  }
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_LAYOUT_BUILDER_HPP
