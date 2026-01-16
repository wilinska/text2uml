#include "config.hpp"
#include <iostream>
#include <sstream>
#include <string>

std::string Config::GetString(const std::string &param_name) const
{
  const auto &it = config.find(param_name);
  if (it != config.end())
  {
    return it->second;
  }
  const auto &def_it = default_values.find(param_name);
  return (def_it == config.end()) ? "" : def_it->second;
}

std::uint32_t Config::GetUInt(const std::string &param_name) const
{
  const auto &it = config.find(param_name);
  if (it != config.end())
  {
    return std::stoi(it->second);
  }
  const auto &def_it = default_values.find(param_name);
  return (def_it == config.end()) ? 0 : std::stoi(def_it->second);
}

double Config::GetDouble(const std::string &param_name) const
{
  const auto &it = config.find(param_name);
  if (it != config.end())
  {
    return std::stod(it->second);
  }
  const auto &def_it = default_values.find(param_name);
  return (def_it == config.end()) ? 0 : std::stod(def_it->second);
}

bool Config::GetBool(const std::string &param_name) const
{
  const auto &it = config.find(param_name);
  if (it != config.end())
  {
    return it->second == "on";
  }
  const auto &def_it = default_values.find(param_name);
  return (def_it == config.end()) ? false : def_it->second == "on";
}

void Config::parseConfig(const std::string &config_json)
{
  if (config_json.empty() || config_json == "{}" ||
      config_json.find_first_not_of(" \t\n") == std::string::npos)
  {
    return;
  }

  std::string trimmed =
      config_json.substr(config_json.find('{') + 1,
                         config_json.rfind('}') - config_json.find('{') - 1);
  if (trimmed.empty())
  {
    return;
  }

  size_t pos = 0;
  while (pos < trimmed.length())
  {
    size_t keyStart = trimmed.find('"', pos);
    if (keyStart == std::string::npos)
      break;
    size_t keyEnd = trimmed.find('"', keyStart + 1);
    if (keyEnd == std::string::npos)
      break;
    std::string key = trimmed.substr(keyStart + 1, keyEnd - keyStart - 1);

    size_t colonPos = trimmed.find(':', keyEnd);
    if (colonPos == std::string::npos)
      break;
    size_t value_start = trimmed.find('"', colonPos);
    if (value_start == std::string::npos)
      break;
    size_t value_end = trimmed.find('"', value_start + 1);
    if (value_end == std::string::npos)
      break;
    std::string value =
        trimmed.substr(value_start + 1, value_end - value_start - 1);

    config[key] = value;

    pos = trimmed.find(',', value_end);
    if (pos == std::string::npos)
      break;
    pos++;
  }

  return;
}
