#include "src/cpp/image_builder/layouts/orthogonal_layout/orthogonal_layout.hpp"
#include "src/cpp/graph/graph.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/orthogonal/OrthoLayout.h>
#include <ogdf/planarity/PlanRep.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include <sstream>
#include <string>
#include <unordered_map>

void OrthogonalGraphLayout::ApplyLayout(const Config &config)
{
  // Planarize the graph using PlanarizationLayout
  ogdf::PlanarizationLayout planarizationLayout;
  planarizationLayout.call(GA);

  // Apply the orthogonal layout algorithm
  ogdf::OrthoLayout orthoLayout;
  orthoLayout.separation(50.0); // Increase separation between nodes
  orthoLayout.margin(50.0);     // Increase margin around the layout

  // Create a planar representation of the graph
  ogdf::PlanRep planRep(GA);

  // Create a Layout object to store the computed layout
  ogdf::Layout drawing(planRep);

  // Compute the orthogonal layout
  orthoLayout.call(planRep, nullptr, drawing);

  // Copy the computed layout back to the GraphAttributes
  for (ogdf::node v : planRep.nodes)
  {
    ogdf::node originalNode = planRep.original(v);
    if (originalNode)
    {
      GA.x(originalNode) = drawing.x(v);
      GA.y(originalNode) = drawing.y(v);
    }
  }
}