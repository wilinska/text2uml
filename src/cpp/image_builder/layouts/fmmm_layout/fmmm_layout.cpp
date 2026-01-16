#include "src/cpp/image_builder/layouts/fmmm_layout/fmmm_layout.hpp"
#include "src/cpp/graph/graph.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/energybased/FMMMLayout.h>
#include <ogdf/energybased/fmmm/FMMMOptions.h>
#include <ogdf/fileformats/GraphIO.h>
#include <sstream>
#include <string>
#include <unordered_map>

ogdf::FMMMOptions::GalaxyChoice getGalaxyChoice(const Config &config)
{
  const auto &galaxy_choice_str = config.GetString("galaxyChoice");
  if (galaxy_choice_str == "UniformProb")
  {
    return ogdf::FMMMOptions::GalaxyChoice::UniformProb;
  }
  else if (galaxy_choice_str == "NonUniformProbHigherMass")
  {
    return ogdf::FMMMOptions::GalaxyChoice::NonUniformProbHigherMass;
  }
  return ogdf::FMMMOptions::GalaxyChoice::NonUniformProbLowerMass;
}

void FMMMGraphLayout::ApplyLayout(const Config &config)
{
  ogdf::FMMMLayout fmmmLayout;
  fmmmLayout.useHighLevelOptions(config.GetBool("useHighLevelOptions"));
  fmmmLayout.unitEdgeLength(config.GetDouble("unitEdgeLength"));
  fmmmLayout.fineTuneScalar(config.GetDouble("fineTuneScalar"));
  fmmmLayout.galaxyChoice(getGalaxyChoice(config));
  fmmmLayout.call(GA);
}
