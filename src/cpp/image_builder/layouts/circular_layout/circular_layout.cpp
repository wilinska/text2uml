#include "src/cpp/image_builder/layouts/circular_layout/circular_layout.hpp"
#include "src/cpp/graph/graph.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/misclayout/CircularLayout.h>
#include <sstream>
#include <string>

void CircularGraphLayout::ApplyLayout(const Config &config)
{
  for (ogdf::node v : G.nodes)
  {
    if (GA.width(v) <= 0)
      GA.width(v) = 50.0;
    if (GA.height(v) <= 0)
      GA.height(v) = 50.0;
  }

  ogdf::CircularLayout circularLayout;
  circularLayout.minDistCircle(
      config.GetDouble("minDistCircle")); // Minimalny odstęp w kole
  circularLayout.minDistLevel(
      config.GetDouble("minDistLevel")); // Odstęp między poziomami
  circularLayout.minDistSibling(
      config.GetDouble("minDistSibling")); // Odstęp między rodzeństwem
  circularLayout.call(GA);
}