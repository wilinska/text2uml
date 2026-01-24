#include "src/cpp/image_builder/layouts/optimal_hierarchy_layout/optimal_hierarchy_layout.hpp"
#include "src/cpp/graph/graph.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/DfsAcyclicSubgraph.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <sstream>
#include <string>
#include <unordered_map>

void OptimalHierarchyGraphLayout::ApplyLayout(const Config &config)
{
  ogdf::SugiyamaLayout SL;
  // Set ranking (layer assignment)
  SL.setRanking(new ogdf::OptimalRanking);
  // Set edge crossing (minimize crossings)
  SL.setCrossMin(new ogdf::MedianHeuristic);
  // Set final layout (node coordinates)
  // OptimalHierarchyLayout determines optimal horizontal positioning
  SL.setLayout(new ogdf::OptimalHierarchyLayout);
  SL.call(GA);
}
