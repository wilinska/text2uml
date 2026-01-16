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

// Funkcja do przesuwania pierwszego lub ostatniego punktu ścieżki SVG
std::string
MovePath(const std::string &path_data, int dx, int dy, bool isSource)
{
  // Podziel ścieżkę na osobne komendy
  std::regex command_regex(
      "([MmLlHhVvCcSsQqTtAaZz][^MmLlHhVvCcSsQqTtAaZz]*)"); // Rozdziel komendy
  std::sregex_iterator iter(path_data.begin(), path_data.end(), command_regex);
  std::sregex_iterator end;
  std::vector<std::string> commands;

  for (; iter != end; ++iter)
  {
    commands.push_back(iter->str());
  }

  if (commands.empty())
  {
    return path_data; // Jeśli nie ma komend, zwróć oryginalną ścieżkę
  }

  // Wybierz komendę do modyfikacji (pierwszą lub ostatnią)
  std::string &target_command = isSource ? commands.front() : commands.back();

  // Wyodrębnij współrzędne z komendy
  std::regex coordRegex("([-+]?[0-9]*\\.?[0-9]+)"); // Dopasuj liczby (całkowite
                                                    // i zmiennoprzecinkowe)
  std::sregex_iterator coordIter(
      target_command.begin(), target_command.end(), coordRegex);
  std::vector<double> coords;

  for (; coordIter != std::sregex_iterator(); ++coordIter)
  {
    coords.push_back(std::stod(coordIter->str())); // Konwersja na double
  }

  if (coords.size() < 2)
  {
    return path_data; // Jeśli nie ma wystarczająco współrzędnych, zwróć
                      // oryginalną ścieżkę
  }

  // Przesuń odpowiedni punkt
  if (isSource)
  {
    // Przesuń pierwszy punkt
    coords[0] += dx;
    coords[1] += dy;
  }
  else
  {
    // Przesuń ostatni punkt
    coords[coords.size() - 2] += dx;
    coords[coords.size() - 1] += dy;
  }

  // Zaktualizuj komendę
  std::ostringstream updated_command;
  updated_command << target_command[0] << coords[0] << ","
                  << coords[1]; // Zachowaj literę polecenia (np. 'M', 'L')
  for (size_t i = 2; i < coords.size(); ++i)
  {
    updated_command << " " << coords[i];
  }
  target_command = updated_command.str();

  // Zaktualizuj atrybut 'd' ścieżki
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
