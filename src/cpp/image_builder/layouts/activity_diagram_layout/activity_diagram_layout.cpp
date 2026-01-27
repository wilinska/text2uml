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

namespace
{
// clang-format off
static const std::unordered_map<char, double> PIXEL_WIDTH_ARIAL_12_MAP = {
    // Big letters
    {'A', 7}, {'B', 7}, {'C', 7}, {'D', 7}, {'E', 6}, {'F', 6}, {'G', 7},
    {'H', 7}, {'I', 3}, {'J', 6}, {'K', 7}, {'L', 6}, {'M', 8}, {'N', 7},
    {'O', 7}, {'P', 7}, {'Q', 7}, {'R', 7}, {'S', 6}, {'T', 7}, {'U', 7},
    {'V', 7}, {'W', 8}, {'X', 7}, {'Y', 7}, {'Z', 7},

    // Small letters
    {'a', 6}, {'b', 7}, {'c', 6}, {'d', 7}, {'e', 6}, {'f', 4}, {'g', 7},
    {'h', 7}, {'i', 3}, {'j', 3}, {'k', 6}, {'l', 3}, {'m', 8}, {'n', 7},
    {'o', 7}, {'p', 7}, {'q', 7}, {'r', 5}, {'s', 6}, {'t', 5}, {'u', 7},
    {'v', 7}, {'w', 8}, {'x', 7}, {'y', 7}, {'z', 6},

    // Digits
    {'0', 6}, {'1', 6}, {'2', 6}, {'3', 6}, {'4', 6}, {'5', 6}, {'6', 6},
    {'7', 6}, {'8', 6}, {'9', 6},

    // Specials signs
    {' ', 3}, {'.', 2}, {',', 2}, {'!', 2}, {'?', 6}, {'-', 4}, {'+', 6},
    {'=', 6}, {'@', 10}, {'#', 8}, {'$', 7}, {'%', 10}, {'&', 8}, {'*', 6},
    {'(', 4}, {')', 4}, {'[', 4}, {']', 4}, {'{', 4}, {'}', 4}, {';', 3},
    {':', 3}, {'"', 4}, {'\'', 2}, {'<', 6}, {'>', 6}, {'/', 6}, {'\\', 6},
};

// clang-format on

double Calculate(std::string text)
{
  double result{0};
  std::for_each(text.begin(),
                text.end(),
                [&result](const char c)
                {
                  const auto it = PIXEL_WIDTH_ARIAL_12_MAP.find(c);
                  if (it != PIXEL_WIDTH_ARIAL_12_MAP.end())
                  {
                    result += it->second;
                  }
                  else
                  {
                    result += PIXEL_WIDTH_ARIAL_12_MAP.at('?');
                  }
                });
  return result;
}

} // namespace

void ActivityDiagramLayout::ApplyLayout(const Config &config)
{
  graph.activity = true;
  ogdf::SugiyamaLayout sugiyama;
  sugiyama.setRanking(new ActivityRanking(GA));
  sugiyama.setCrossMin(new ogdf::MedianHeuristic);
  ogdf::FastHierarchyLayout *fastHierarchyLayout =
      new ogdf::FastHierarchyLayout;
  fastHierarchyLayout->layerDistance(config.GetDouble("edgeMinLength"));
  fastHierarchyLayout->nodeDistance(20);
  sugiyama.setLayout(fastHierarchyLayout);
  sugiyama.call(GA);

  for (ogdf::node v : G.nodes)
  {
    if (GA.label(v) == "SWIMLANE_PLACEHOLDER_NODE")
    {
      continue;
    }
    if (std::stoi(GA.label(v)))
    {
      if (graph.nodes_order.size() <= std::stoull(GA.label(v)))
      {
        std::cerr << "ActivityDiagramLayout::ApplyLayout: Node index "
                  << GA.label(v) << " out of bounds." << std::endl;
        continue;
      }
      const auto &graph_node =
          graph.nodes.at(graph.nodes_order.at(std::stoi(GA.label(v))));
      if (graph_node.activity_enum_type == ActivityTypeEnum::Fork)
      {
        double minX = std::numeric_limits<double>::max();
        double maxX = std::numeric_limits<double>::lowest();
        bool hasTargets = false;
        // 1. Najpierw znajdź skrajne wartości X wierzchołków docelowych
        for (ogdf::adjEntry adj : v->adjEntries)
        {
          if (adj->isSource())
          {
            ogdf::node target = adj->twinNode();
            double tx = GA.x(target);
            if (tx < minX)
              minX = tx - GA.width(target) / 2;
            if (tx > maxX)
              maxX = tx + GA.width(target) / 2;
            hasTargets = true;
          }
        }

        if (hasTargets)
        {
          double padding = 20.0;
          double newWidth = (maxX - minX) + padding;
          GA.width(v) = std::max(newWidth, 40.0);
        }
      }
    }
  }
  sugiyama.call(GA);

  double offset_y = 30.0;
  for (auto v : G.nodes)
  {
    if (GA.label(v) == "SWIMLANE_PLACEHOLDER_NODE")
    {
      continue;
    }
    GA.y(v) += offset_y;
  }
  // Post-process edges from fork nodes to enforce vertical segments
  for (ogdf::node v : G.nodes)
  {
    if (GA.label(v) == "SWIMLANE_PLACEHOLDER_NODE")
    {
      continue;
    }
    if (std::stoi(GA.label(v)))
    {
      if (graph.nodes_order.size() <= std::stoull(GA.label(v)))
      {
        std::cerr << "ActivityDiagramLayout::ApplyLayout: Node index "
                  << GA.label(v) << " out of bounds." << std::endl;
        continue;
      }
      const auto &graph_node =
          graph.nodes.at(graph.nodes_order.at(std::stoi(GA.label(v))));
      if (graph_node.activity_enum_type == ActivityTypeEnum::Fork)
      {
        double minX = std::numeric_limits<double>::max();
        double maxX = std::numeric_limits<double>::lowest();
        bool hasTargets = false;
        for (ogdf::adjEntry adj : v->adjEntries)
        {
          if (adj->isSource())
          {
            ogdf::node target = adj->twinNode();
            double tx = GA.x(target);
            if (tx < minX)
              minX = tx - GA.width(target) / 2;
            if (tx > maxX)
              maxX = tx + GA.width(target) / 2;
            hasTargets = true;
          }
        }

        if (hasTargets)
        {
          double padding = 20.0;
          double newWidth = (maxX - minX) + padding;

          GA.width(v) = std::max(newWidth, 40.0);

          for (ogdf::adjEntry adj : v->adjEntries)
          {
            if (adj->isSource())
            {
              ogdf::node target = adj->twinNode();
              ogdf::edge e = adj->theEdge();

              ogdf::DPolyline &bends = GA.bends(e);
              bends.clear();

              double x = GA.x(target);
              double yStart = GA.y(v) + GA.height(v) / 2;

              bends.pushBack(ogdf::DPoint(x, yStart));
            }
          }
        }
        else
        {
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
  // Przechowuje min i max X dla każdego swimlane'u ZANIM zaczniemy przesuwać
  std::unordered_map<int, std::pair<double, double>> swimlane_bounds;

  // 1. Grupowanie i znalezienie pierwotnych granic X dla każdego toru
  for (ogdf::node v : G.nodes)
  {
    if (GA.label(v) == "SWIMLANE_PLACEHOLDER_NODE")
      continue;

    std::string name = swimlaneMap[v];
    if (graph.swimlanes_ids.find(name) == graph.swimlanes_ids.end())
    {
      int id = maxSwimlane++;
      graph.swimlanes_ids[name] = id;
      graph.swimlanes[id].name = name;
      swimlane_bounds[id] = {GA.x(v) - GA.width(v) / 2,
                             GA.x(v) + GA.width(v) / 2};
    }
    else
    {
      int id = graph.swimlanes_ids[name];
      swimlane_bounds[id].first =
          std::min(swimlane_bounds[id].first, GA.x(v) - GA.width(v) / 2);
      swimlane_bounds[id].second =
          std::max(swimlane_bounds[id].second, GA.x(v) + GA.width(v) / 2);
    }
  }

  // 2. Obliczanie szerokości i nowych offsetów (gdzie dany tor się ZACZYNA)
  double currentXStart = 0.0;
  double swimlanePadding = 40.0; // Odstęp wewnątrz toru
  double swimlaneSpacing = 20.0; // Odstęp między torami

  std::vector<double> laneOffsets(maxSwimlane);
  std::vector<double> originalLaneMinX(maxSwimlane);

  for (int i = 0; i < maxSwimlane; i++)
  {
    double contentWidth = swimlane_bounds[i].second - swimlane_bounds[i].first;
    double labelWidth = Calculate(graph.swimlanes[i].name);

    graph.swimlanes[i].width =
        std::max(contentWidth, labelWidth) + (swimlanePadding * 2);
    graph.swimlanes[i].x = currentXStart;

    laneOffsets[i] = currentXStart;
    originalLaneMinX[i] = swimlane_bounds[i].first;

    currentXStart += graph.swimlanes[i].width + swimlaneSpacing;
  }

  // 3. Przesunięcie węzłów: NowyX = StartToru + (StaryX - MinXToru) + Padding
  for (ogdf::node v : G.nodes)
  {
    if (GA.label(v) == "SWIMLANE_PLACEHOLDER_NODE")
      continue;

    int id = graph.swimlanes_ids[swimlaneMap[v]];
    double relativeX =
        GA.x(v) -
        originalLaneMinX[id]; // Pozycja względem początku danych w torze
    GA.x(v) = laneOffsets[id] + relativeX + swimlanePadding;

    graph.height = std::max(graph.height, GA.y(v) + GA.height(v));
  }

  // 4. Przesunięcie krawędzi (Bends)
  for (ogdf::edge e : G.edges)
  {
    ogdf::node source = e->source();
    ogdf::node target = e->target();

    int srcId = graph.swimlanes_ids[swimlaneMap[source]];
    int tgtId = graph.swimlanes_ids[swimlaneMap[target]];

    ogdf::DPolyline &bends = GA.bends(e);
    for (auto &point : bends)
    {
      // Prosta heurystyka: przesuwamy bend o uśredniony offset obu torów,
      // lub o offset toru źródłowego jeśli krawędź jest wewnętrzna.
      if (srcId == tgtId)
      {
        // Krawędź wewnątrz jednego toru
        point.m_x = laneOffsets[srcId] + (point.m_x - originalLaneMinX[srcId]) +
                    swimlanePadding;
      }
      else
      {
        // Krawędź między torami - tu sprawa jest złożona, najlepiej wyczyścić
        // bends lub przesunąć o offset proporcjonalny. Na początek:
        point.m_x +=
            (laneOffsets[srcId] - originalLaneMinX[srcId] + swimlanePadding);
      }
    }
  }
}
