#ifndef SRC_CPP_CONFIG_CONFIG_HPP
#define SRC_CPP_CONFIG_CONFIG_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

class Config
{
public:
  Config(const std::string &config_json) { parseConfig(config_json); }

  std::string GetString(const std::string &param_name) const;
  std::uint32_t GetUInt(const std::string &param_name) const;
  double GetDouble(const std::string &param_name) const;
  bool GetBool(const std::string &param_name) const;

private:
  void parseConfig(const std::string &config_json);

  const std::unordered_map<std::string, std::string> default_values{
      {"rankingType", "OptimalRanking"},
      {"crossMinType", "MedianHeuristic"},
      {"layerDistance", "30"},
      {"nodeDistance", "25"},
      {"weightBalancing", "0.8"},
      {"minSeparation", "50"},
      {"minDistCircle", "100"},
      {"minDistLevel", "100"},
      {"minDistSibling", "70"},
      {"useHighLevelOptions", "on"},
      {"fineTuneScalar", "0.2"},
      {"galaxyChoice", "NonUniformProbLowerMass"},
      {"unitEdgeLength", "75"}};

  std::unordered_map<std::string, std::string> config{};
};

#endif // SRC_CPP_CONFIG_CONFIG_HPP
