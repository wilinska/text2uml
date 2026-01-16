#ifndef SRC_CPP_IMAGE_BUILDER_LAYOUTS_ACTIVITY_DIAGRAM_LAYOUT_ACTIVITY_RANKING_HPP
#define SRC_CPP_IMAGE_BUILDER_LAYOUTS_ACTIVITY_DIAGRAM_LAYOUT_ACTIVITY_RANKING_HPP
#include "src/cpp/image_builder/layouts/activity_diagram_layout/activity_diagram_layout.hpp"
#include <iostream>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/OptimalRanking.h>
#include <queue>

class ActivityRanking : public ogdf::RankingModule
{
public:
  explicit ActivityRanking(ogdf::GraphAttributes &GA) : GA_(GA) {}

  void call(const ogdf::Graph &G, ogdf::NodeArray<int> &rank) override;

private:
  ogdf::GraphAttributes &GA_;
};

#endif // SRC_CPP_IMAGE_BUILDER_LAYOUTS_ACTIVITY_DIAGRAM_LAYOUT_ACTIVITY_RANKING_HPP
