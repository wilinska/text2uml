#include "src/cpp/image_builder/layouts/sugiyama_layout/sugiyama_layout.hpp"
#include "src/cpp/graph/graph.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/BarycenterHeuristic.h>
#include <ogdf/layered/CoffmanGrahamRanking.h>
#include <ogdf/layered/FastHierarchyLayout.h>
#include <ogdf/layered/GreedyInsertHeuristic.h>
#include <ogdf/layered/GreedySwitchHeuristic.h>
#include <ogdf/layered/LongestPathRanking.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/SplitHeuristic.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/uml/UMLCrossingMinimizationModule.h>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

std::string postProcessSVG(const std::string &svg)
{
  // Replace sequences "M x1,y1 L cx,cy L x2,y2" with "M x1,y1 Q cx,cy x2,y2"
  std::regex line_pattern(
      R"(M\s+(\d+\.\d+),(\d+\.\d+)\s+L\s+(\d+\.\d+),(\d+\.\d+)\s+L\s+(\d+\.\d+),(\d+\.\d+))");
  std::string result =
      std::regex_replace(svg, line_pattern, "M $1,$2 Q $3,$4 $5,$6");
  return result;
}

void SetRanking(ogdf::SugiyamaLayout &layout, const Config &config)
{
  const auto &ranking_str = config.GetString("rankingType");
  static const std::unordered_map<std::string,
                                  std::function<ogdf::RankingModule *()>>
      ranking_map = {
          {"OptimalRanking", []() { return new ogdf::OptimalRanking; }},
          {"LongestPathRanking", []() { return new ogdf::LongestPathRanking; }},
          {"CoffmanGrahamRanking",
           []() { return new ogdf::CoffmanGrahamRanking; }}};

  const auto &ranking_it = ranking_map.find(ranking_str);
  layout.setRanking(ranking_it != ranking_map.end() ? ranking_it->second()
                                                    : new ogdf::OptimalRanking);
}

void SetCrossMin(ogdf::SugiyamaLayout &layout, const Config &config)
{
  const auto &crossmin_str = config.GetString("crossMinType");

  static const std::unordered_map<std::string,
                                  std::function<ogdf::LayerByLayerSweep *()>>
      crossmin_map = {
          {"BarycenterHeuristic",
           []() { return new ogdf::BarycenterHeuristic; }},
          {"MedianHeuristic", []() { return new ogdf::MedianHeuristic; }},
          {"GreedyInsertHeuristic",
           []() { return new ogdf::GreedyInsertHeuristic; }},
          {"GreedySwitchHeuristic",
           []() { return new ogdf::GreedySwitchHeuristic; }},
          {"SplitHeuristic", []() { return new ogdf::SplitHeuristic; }}};

  const auto &crossmin_it = crossmin_map.find(crossmin_str);
  layout.setCrossMin(crossmin_it != crossmin_map.end()
                         ? crossmin_it->second()
                         : new ogdf::BarycenterHeuristic);
}

void SugiyamaGraphLayout::ApplyLayout(const Config &config)
{
  // Apply the Sugiyama layout algorithm
  ogdf::SugiyamaLayout sugiyamaLayout;

  SetRanking(sugiyamaLayout, config);
  SetCrossMin(sugiyamaLayout, config);

  ogdf::FastHierarchyLayout *fastHierarchyLayout =
      new ogdf::FastHierarchyLayout;
  fastHierarchyLayout->layerDistance(
      config.GetDouble("layerDistance")); // Distance between layers
  fastHierarchyLayout->nodeDistance(config.GetDouble(
      "nodeDistance")); // Distance between nodes in the same layer
  sugiyamaLayout.setLayout(fastHierarchyLayout);

  // Compute the layout
  sugiyamaLayout.call(GA);
}
