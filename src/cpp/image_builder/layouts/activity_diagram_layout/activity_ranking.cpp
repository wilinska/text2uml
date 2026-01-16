#include "src/cpp/image_builder/layouts/activity_diagram_layout/activity_ranking.hpp"
#include "src/cpp/image_builder/layouts/activity_diagram_layout/activity_diagram_layout.hpp"
#include <iostream>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/OptimalRanking.h>
#include <queue>

void ActivityRanking::call(const ogdf::Graph &G, ogdf::NodeArray<int> &rank)
{
  rank.init(G, 0);
  int ranked = 0;

  int nodeCount = 0;
  for (auto v : G.nodes)
  {
    std::ignore = v;
    nodeCount++;
  }

  bool first = true;
  while (ranked < nodeCount)
  {
    for (ogdf::node v : G.nodes)
    {
      if (first && GA_.label(v) == "0")
      {
        rank[v] = 1;
        first = false;
        ranked++;
      }
      if (rank[v] == 0)
      {
        continue;
      }
      for (auto adj : v->adjEntries)
      {
        if (adj->isSource())
        {
          rank[adj->twinNode()] = std::max(rank[adj->twinNode()], rank[v] + 1);
          ranked++;
        }
      }
    }
  }

  std::queue<ogdf::node> nodeQueue;
  for (auto v : G.nodes)
  {
    nodeQueue.push(v);
  }

  while (!nodeQueue.empty())
  {
    auto v = nodeQueue.front();
    nodeQueue.pop();

    for (ogdf::adjEntry adj : v->adjEntries)
    {
      if (adj->isSource())
      {
        auto target = adj->twinNode();
        int oldRank = rank[target];
        int newRank = std::max(rank[target], rank[v] + 1);

        if (newRank > oldRank)
        {
          rank[target] = newRank;
          nodeQueue.push(target);
        }
      }
    }
  }
}
