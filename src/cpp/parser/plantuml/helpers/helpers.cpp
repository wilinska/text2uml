#include "src/cpp/parser/plantuml/helpers/helpers.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>

std::tuple<double, double> extractCoordinates(const std::string &input)
{
  size_t start = input.find('(');
  size_t comma = input.find(',');
  size_t end = input.find(')');

  if (start == std::string::npos || comma == std::string::npos ||
      end == std::string::npos)
  {
    return {0, 0};
  }

  std::string dxStr = input.substr(start + 1, comma - (start + 1));
  std::string dyStr = input.substr(comma + 1, end - (comma + 1));

  // Usuń białe znaki
  dxStr.erase(0, dxStr.find_first_not_of(' '));
  dxStr.erase(dxStr.find_last_not_of(' ') + 1);
  dyStr.erase(0, dyStr.find_first_not_of(' '));
  dyStr.erase(dyStr.find_last_not_of(' ') + 1);

  // Sprawdź, czy dxStr i dyStr zawierają tylko cyfry, minus i kropkę
  for (char ch : dxStr)
  {
    if (!isdigit(ch) && ch != '-' && ch != '.')
    {
      return {0, 0};
    }
  }
  for (char ch : dyStr)
  {
    if (!isdigit(ch) && ch != '-' && ch != '.')
    {
      return {0, 0};
    }
  }

  double dx = std::stod(dxStr);
  double dy = std::stod(dyStr);

  return {dx, dy};
}
