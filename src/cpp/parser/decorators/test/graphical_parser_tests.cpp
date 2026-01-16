#include "src/cpp/parser/plantuml/class_diagram/parser.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

namespace test
{

using ::testing::ElementsAre;

TEST(ParserTest, ReadOneClassDiagram)
{

  std::string input =
      "@startuml\n"
      "\n"
      "class Car {\n"
      "integer attr\n"
      "}\n"
      "\n"
      "@enduml\n"
      "";

  class_diagram::GeneratedParser parser;
  const auto &graph = parser.Parse(input, true);

  ASSERT_EQ(graph.nodes.size(), 1);

  const auto node = graph.nodes.at(0);
  EXPECT_EQ(node.label, "Car");
  EXPECT_EQ(node.id, 0);

  ASSERT_EQ(node.attributes.size(), 1);
  EXPECT_THAT(node.attributes, ElementsAre("integer attr"));

  ASSERT_EQ(graph.edges.size(), 0);
}

TEST(ParserTest, ReadOneClassDiagramWithTwoAttributes)
{

  std::string input =
      "@startuml\n"
      "\n"
      "class Car {\n"
      "attr\n"
      "integer attr2\n"
      "}\n"
      "\n"
      "@enduml\n"
      "";

  class_diagram::GeneratedParser parser;
  const auto &graph = parser.Parse(input, true);

  ASSERT_EQ(graph.nodes.size(), 1);

  const auto node = graph.nodes.at(0);
  EXPECT_EQ(node.label, "Car");
  EXPECT_EQ(node.id, 0);

  ASSERT_EQ(node.attributes.size(), 2);
  EXPECT_THAT(node.attributes, ElementsAre("integer attr2", "attr"));

  ASSERT_EQ(node.methods.size(), 0);

  ASSERT_EQ(graph.edges.size(), 0);
}

} // namespace test
