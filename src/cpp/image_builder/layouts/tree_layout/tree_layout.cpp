#include "src/cpp/image_builder/layouts/tree_layout/tree_layout.hpp"
#include "src/cpp/graph/graph.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include <ogdf/tree/TreeLayout.h>
#include <sstream>
#include <string>

void TreeGraphLayout::ApplyLayout(const Config &config)
{
  double minSeparation = 50.0; // Minimalny odstęp między wierzchołkami

  // Ustaw domyślne rozmiary wierzchołków
  for (ogdf::node v : G.nodes)
  {
    if (GA.width(v) <= 0)
      GA.width(v) = 50.0;
    if (GA.height(v) <= 0)
      GA.height(v) = 50.0;
  }

  // Jeśli graf nie jest drzewem, użyj PlanarizationLayout jako bazy
  ogdf::PlanarizationLayout planarizationLayout;
  planarizationLayout.call(GA);

  // Zastosuj TreeLayout
  ogdf::TreeLayout treeLayout;
  treeLayout.levelDistance(minSeparation + 50.0); // Odstęp między poziomami
  treeLayout.siblingDistance(minSeparation + 20.0); // Odstęp między rodzeństwem
  treeLayout.treeDistance(minSeparation + 50.0); // Odstęp między poddrzewami
  treeLayout.orientation(
      ogdf::Orientation::topToBottom); // Orientacja od góry do dołu

  treeLayout.call(GA);
}