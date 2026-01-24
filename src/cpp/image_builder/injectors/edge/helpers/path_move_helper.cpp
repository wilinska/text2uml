#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace helpers
{
namespace svg
{
namespace path
{

// Function to move the first or last point of an SVG path
std::string
MovePath(const std::string &path_data, int dx, int dy, bool isSource)
{
  // Split path into separate commands
  std::regex command_regex(
      "([MmLlHhVvCcSsQqTtAaZz][^MmLlHhVvCcSsQqTtAaZz]*)"); // Split commands
  std::sregex_iterator iter(path_data.begin(), path_data.end(), command_regex);
  std::sregex_iterator end;
  std::vector<std::string> commands;

  for (; iter != end; ++iter)
  {
    commands.push_back(iter->str());
  }

  if (commands.empty())
  {
    return path_data; // If there are no commands, return original path
  }

  // Select command to modify (first or last)
  std::string &target_command = isSource ? commands.front() : commands.back();

  // Extract coordinates from command
  std::regex coordRegex("([-+]?[0-9]*\\.?[0-9]+)"); // Match numbers (integer
                                                    // and floating-point)
  std::sregex_iterator coordIter(
      target_command.begin(), target_command.end(), coordRegex);
  std::vector<double> coords;

  for (; coordIter != std::sregex_iterator(); ++coordIter)
  {
    coords.push_back(std::stod(coordIter->str())); // Konwersja na double
  }

  if (coords.size() < 2)
  {
    return path_data; // If there aren't enough coordinates, return
                      // original path
  }

  // Move appropriate point
  if (isSource)
  {
    // Move first point
    coords[0] += dx;
    coords[1] += dy;
  }
  else
  {
    // Move last point
    coords[coords.size() - 2] += dx;
    coords[coords.size() - 1] += dy;
  }

  // Update command
  std::ostringstream updated_command;
  updated_command << target_command[0] << coords[0] << ","
                  << coords[1]; // Keep command letter (e.g., 'M', 'L')
  for (size_t i = 2; i < coords.size(); ++i)
  {
    updated_command << " " << coords[i];
  }
  target_command = updated_command.str();

  // Update 'd' attribute of path
  std::ostringstream updated_path_data;
  for (const auto &cmd : commands)
  {
    updated_path_data << cmd;
  }

  return updated_path_data.str();
}

} // namespace path
} // namespace svg
} // namespace helpers
