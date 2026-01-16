#include "src/cpp/image_builder/layouts/activity_diagram_layout/activity_diagram_layout.hpp"
#include "src/cpp/image_builder/layouts/activity_diagram_layout/activity_ranking.hpp"
#include <iostream>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/FastHierarchyLayout.h>
#include <ogdf/layered/HierarchyClusterLayoutModule.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <queue>

void ActivityDiagramLayout::ApplyLayout(const Config &config)
{
  graph.activity = true;
  ogdf::SugiyamaLayout sugiyama;
  sugiyama.setRanking(new ActivityRanking(GA));
  sugiyama.setCrossMin(new ogdf::MedianHeuristic);

  ogdf::FastHierarchyLayout *fastHierarchyLayout =
      new ogdf::FastHierarchyLayout;
  fastHierarchyLayout->layerDistance(50);
  fastHierarchyLayout->nodeDistance(20);
  sugiyama.setLayout(fastHierarchyLayout);

  sugiyama.call(GA);

  double offset_y = 30.0;
  for (auto v : G.nodes)
  {
    GA.y(v) += offset_y;
  }

  // Post-process edges from fork nodes to enforce vertical segments
  for (ogdf::node v : G.nodes)
  {
    if (std::stoi(GA.label(v)))
    {
      const auto &graph_node =
          graph.nodes.at(graph.nodes_order.at(std::stoi(GA.label(v))));

      if (graph_node.activity_enum_type == ActivityTypeEnum::Fork)
      {
        for (ogdf::adjEntry adj : v->adjEntries)
        {
          if (adj->isSource())
          {
            std::ignore = graph_node;

            ogdf::node target = adj->twinNode();
            ogdf::edge e = adj->theEdge();
            // Ensure edge starts at fork node and ends at target with same
            // x-coordinate
            ogdf::DPolyline &bends = GA.bends(e);
            bends.clear(); // Remove existing bends
            // Add a single vertical segment
            double x = GA.x(target); // Use fork node's x-coordinate
            double y1 = GA.y(v) + GA.height(v) / 2; // Bottom of fork node
            // target
            bends.pushBack(ogdf::DPoint(x, y1));
          }
        }
      }
      else if (graph_node.activity_enum_type == ActivityTypeEnum::Conditional)
      {
        for (ogdf::adjEntry adj : v->adjEntries)
        {
          if (adj->isSource())
          {
            ogdf::node target = adj->twinNode();
            ogdf::edge e = adj->theEdge();
            // Ensure edge starts at fork node and ends at target with same
            // x-coordinate
            ogdf::DPolyline &bends = GA.bends(e);
            bends.clear(); // Remove existing bends

            // Add a single vertical segment
            double x = GA.x(target); // Use fork node's x-coordinate
            double y = GA.y(v);

            bends.pushBack(ogdf::DPoint(x, y));
          }
        }
      }
      else if (graph_node.activity_enum_type == ActivityTypeEnum::EndMerge)
      {
        for (ogdf::adjEntry adj : v->adjEntries)
        {
          if (!adj->isSource())
          {
            ogdf::node source = adj->twinNode();
            ogdf::edge e = adj->theEdge();
            // Ensure edge starts at fork node and ends at source with
            // same x-coordinate
            ogdf::DPolyline &bends = GA.bends(e);
            bends.clear(); // Remove existing bends
            // Add a single vertical segment
            double x = GA.x(source); // Use fork node's x-coordinate
            double y = GA.y(v);
            // source
            bends.pushBack(ogdf::DPoint(x, y));
          }
        }
      }
    }
  }

  if (swimlane_map.has_value())
  { // Apply the swimlane layout
    CreateHorizontalSwimlaneLayout(G, GA, swimlane_map.value());
  }
}

void ActivityDiagramLayout::CreateHorizontalSwimlaneLayout(
    ogdf::Graph &G,
    ogdf::GraphAttributes &GA,
    ogdf::NodeArray<std::string> &swimlaneMap)
{
  int maxSwimlane = 0;

  std::unordered_map<int, std::pair<double, double>> swimlane_min_max;
  for (ogdf::node v : G.nodes)
  {
    if (graph.swimlanes_ids.find(swimlaneMap[v]) == graph.swimlanes_ids.end())
    {
      graph.swimlanes_ids[swimlaneMap[v]] = maxSwimlane++;
      swimlane_min_max[maxSwimlane - 1] =
          std::make_pair(GA.x(v) - GA.width(v) / 2, GA.x(v) + GA.width(v) / 2);
      graph.swimlanes[maxSwimlane - 1].name = swimlaneMap[v];
    }

    const auto &swimlane_id = graph.swimlanes_ids[swimlaneMap[v]];
    if (swimlane_min_max[swimlane_id].first > GA.x(v) - GA.width(v) / 2)
    {
      swimlane_min_max[swimlane_id].first = GA.x(v) - GA.width(v) / 2;
    }

    if (swimlane_min_max[swimlane_id].second < GA.x(v) + GA.width(v) / 2)
    {
      swimlane_min_max[swimlane_id].second = GA.x(v) + GA.width(v) / 2;
    }
  }

  // Step 4: Adjust node positions for horizontal swimlanes
  double swimlaneSpacing = 50.0; // Spacing between swimlanes

  std::unordered_map<int, int> swimlanes_offsets_map;
  swimlanes_offsets_map[0] = 0;
  graph.swimlanes[0].x = 0;
  graph.swimlanes[0].width =
      swimlane_min_max[0].second - swimlane_min_max[0].first;

  for (auto i = 1; i < maxSwimlane; i++)
  {
    swimlanes_offsets_map[i] = swimlanes_offsets_map[i - 1];
    swimlanes_offsets_map[i] +=
        swimlane_min_max[i - 1].second - swimlane_min_max[i - 1].first;
    // offset
    swimlanes_offsets_map[i] += swimlaneSpacing;

    graph.swimlanes[i].x =
        graph.swimlanes[i - 1].x + graph.swimlanes[i - 1].width;
    graph.swimlanes[i].width = swimlane_min_max[i].second -
                               swimlane_min_max[i].first + swimlaneSpacing;
  }

  for (ogdf::node v : G.nodes)
  {
    GA.x(v) += swimlanes_offsets_map[graph.swimlanes_ids[swimlaneMap[v]]];

    graph.height = std::max(graph.height, GA.y(v) + GA.height(v));
  }

  swimlanes_offsets_map[0] = 0;
  graph.swimlanes[0].x = 1;
  graph.swimlanes[0].width =
      swimlane_min_max[0].second - swimlane_min_max[0].first + 90;

  for (auto i = 1; i < maxSwimlane; i++)
  {
    graph.swimlanes[i].x =
        graph.swimlanes[i - 1].x + graph.swimlanes[i - 1].width;
    graph.swimlanes[i].width =
        swimlane_min_max[i].second - swimlane_min_max[i].first + 90;
  }

  for (ogdf::edge e : G.edges)
  {
    ogdf::node target = e->target();
    int swimlane_id = graph.swimlanes_ids[swimlaneMap[target]];
    double offset = swimlanes_offsets_map[swimlane_id];

    ogdf::DPolyline &bends = GA.bends(e);
    for (auto &point : bends)
    {
      point.m_x += offset;
    }
  }
}
