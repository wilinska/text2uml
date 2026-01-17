#include "src/cpp/image_builder/injectors/edge/helpers/path_helper.hpp"
#include "src/cpp/utils/geometry/point.hpp"
#include "src/cpp/utils/geometry/utils.hpp"
#include <cmath>
#include <iostream>
#include <regex>
#include <sstream>

namespace helpers
{
namespace svg
{
namespace path
{

namespace path_helpers
{

struct Point
{
  double x, y;
  Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

// Oblicza długość odcinka między dwoma punktami
double segmentLength(const Point &p1, const Point &p2)
{
  return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

// Interpoluje punkt na odcinku między p1 i p2 na podstawie pozostałej długości
Point interpolatePoint(const Point &p1, const Point &p2, double remainingLength)
{
  double totalLength = segmentLength(p1, p2);
  if (totalLength == 0)
    return p1;
  double t = remainingLength / totalLength;
  return Point(p1.x + t * (p2.x - p1.x), p1.y + t * (p2.y - p1.y));
}

// Funkcja skracająca ścieżkę o zadany odcinek
std::string
shortenPath(const std::string &pathData, double shortenBy, bool start)
{
  std::vector<Point> points;
  std::regex pointRegex(
      "[MLC]\\s*(\\d+\\.?\\d*),(\\d+\\.?\\d*)"); // Parsuje M, L, C
  auto matches =
      std::sregex_iterator(pathData.begin(), pathData.end(), pointRegex);
  auto end = std::sregex_iterator();

  std::string commandOrder; // Zachowuje kolejność komend (M, L, C)
  for (auto it = matches; it != end; ++it)
  {
    commandOrder += (*it).str()[0]; // Pierwszy znak (M, L, C)
    double x = std::stod((*it)[1].str());
    double y = std::stod((*it)[2].str());
    points.emplace_back(x, y);
  }

  if (points.size() < 2)
    return pathData; // Za mało punktów

  std::ostringstream newPath;
  double remainingLength = shortenBy;

  if (start)
  {
    // Skracanie od początku
    size_t i = 0;
    double cumulativeLength = 0;

    while (i < points.size() - 1 && remainingLength > 0)
    {
      double segLength = segmentLength(points[i], points[i + 1]);
      cumulativeLength += segLength;

      if (cumulativeLength >= remainingLength)
      {
        Point newStart =
            interpolatePoint(points[i],
                             points[i + 1],
                             segLength - (cumulativeLength - remainingLength));
        newPath << "M " << newStart.x << "," << newStart.y << " ";
        for (size_t j = i + 1; j < points.size(); ++j)
        {
          if (commandOrder[j] == 'C' && j + 2 < points.size())
          {
            newPath << "C " << points[j].x << "," << points[j].y << " "
                    << points[j + 1].x << "," << points[j + 1].y << " "
                    << points[j + 2].x << "," << points[j + 2].y << " ";
            j += 2;
          }
          else
          {
            newPath << "L " << points[j].x << "," << points[j].y << " ";
          }
        }
        break;
      }
      ++i;
    }
    if (remainingLength <= 0 || i >= points.size() - 1)
    {
      return pathData; // Nie zmieniamy, jeśli za mało do skrócenia
    }
  }
  else
  {
    // Skracanie od końca
    size_t i = points.size() - 1;
    double cumulativeLength = 0;

    newPath << "M " << points[0].x << "," << points[0].y << " ";
    while (i > 0 && remainingLength > 0)
    {
      double segLength = segmentLength(points[i - 1], points[i]);
      cumulativeLength += segLength;

      if (cumulativeLength >= remainingLength)
      {
        Point newEnd = interpolatePoint(
            points[i - 1], points[i], cumulativeLength - remainingLength);
        for (size_t j = 1; j < i; ++j)
        {
          if (commandOrder[j] == 'C' && j + 2 <= i)
          {
            newPath << "C " << points[j].x << "," << points[j].y << " "
                    << points[j + 1].x << "," << points[j + 1].y << " "
                    << points[j + 2].x << "," << points[j + 2].y << " ";
            j += 2;
          }
          else
          {
            newPath << "L " << points[j].x << "," << points[j].y << " ";
          }
        }
        newPath << "L " << newEnd.x << "," << newEnd.y;
        break;
      }
      --i;
    }
    if (remainingLength <= 0 || i <= 0)
    {
      return pathData; // Nie zmieniamy, jeśli za mało do skrócenia
    }
  }

  return newPath.str();
}
} // namespace path_helpers

using Point = utils::geometry::Point;

inline bool
AreEqual(const double a, const double b, const double epsilon = 1e-9)
{
  return std::fabs(a - b) < epsilon;
}

inline bool
LessOrEqual(const double a, const double b, const double epsilon = 1e-9)
{
  return a - epsilon <= b;
}

inline bool
MoreOrEqual(const double a, const double b, const double epsilon = 1e-9)
{
  return a + epsilon >= b;
}

std::string UpdateFirstPoint(const std::string &path, const Point &point)
{
  std::string updated_path{path};
  std::smatch matches;
  const std::regex point_pattern(
      R"([ML]\s*(-?\d+(\.\d+)?)\s*,\s*(-?\d+(\.\d+)?))");

  if (std::regex_search(updated_path, matches, point_pattern))
  {
    std::string new_point = matches[0].str()[0] + std::to_string(point.x) +
                            "," + std::to_string(point.y);
    updated_path.replace(matches.position(0), matches.length(0), new_point);
  }

  return updated_path;
}

std::vector<Point> GetFirstTwoPoints(const std::string &path)
{
  std::vector<Point> points;
  std::smatch matches;
  std::string::const_iterator search_start(path.cbegin());
  const std::regex point_pattern(
      R"([ML]\s*(-?\d+(\.\d+)?)\s*,\s*(-?\d+(\.\d+)?))");
  // Szukaj wszystkich punktów
  while (std::regex_search(search_start, path.cend(), matches, point_pattern))
  {
    Point point{0, 0};
    point.x = std::stod(matches[1]);
    point.y = std::stod(matches[3]);
    points.push_back(point);

    // Przesuń początek wyszukiwania
    search_start = matches.suffix().first;

    if (points.size() == 2)
    {
      break;
    }
  }

  return points;
}

struct Command
{
  char type; // 'M' lub 'L'
  double x;
  double y;
};

std::string Shorten(const std::string &path, const double shortening)
{
  // Wyrażenie regularne do znajdowania par punktów w formacie "Mx,y" lub "Lx,y"
  std::regex point_pattern(R"(([ML]\s*(-?\d+(\.\d+)?)\s*,\s*(-?\d+(\.\d+)?)))");
  std::smatch matches;
  std::vector<std::pair<double, double>> points;
  std::vector<std::string> markers;

  // Szukaj wszystkich dopasowań dla par punktów
  std::string::const_iterator searchStart(path.cbegin());
  while (std::regex_search(searchStart, path.cend(), matches, point_pattern))
  {
    // Wyciągnij marker (M lub L) i współrzędne punktu
    markers.push_back(matches.str().substr(0, 1)); // Pobierz 'M' lub 'L'
    double x = std::stod(matches[2]);
    double y = std::stod(matches[4]);
    points.emplace_back(x, y);

    // Przesuń początek wyszukiwania
    searchStart = matches.suffix().first;
  }

  // Sprawdź, czy znaleziono co najmniej dwa punkty
  if (points.size() < 2)
  {
    std::cerr << "Nie znaleziono wystarczającej liczby punktów." << std::endl;
    return path;
  }

  // Pobierz dwie ostatnie pary punktów
  auto [x1, y1] = points[points.size() - 2];
  auto [x2, y2] = points.back();

  // Oblicz nowe współrzędne punktu końcowego po skróceniu odcinka
  double segment_length =
      std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  if (shortening >= segment_length)
  {
    return path; // Jeśli skrócenie jest większe od długości, zwróć oryginalne
                 // `d`
  }
  double ratio = (segment_length - shortening) / segment_length;
  double new_x2 = x1 + (x2 - x1) * ratio;
  double new_y2 = y1 + (y2 - y1) * ratio;

  // Zbuduj nowe d bez ostatniej pary punktów, dodaj znacznik i nowe współrzędne
  std::ostringstream new_d;
  for (size_t i = 0; i < points.size() - 1; ++i)
  {
    new_d << markers[i] << points[i].first << "," << points[i].second << " ";
  }

  // Dodaj nową końcową parę punktów ze znakiem 'L' dla linii
  new_d << "L" << new_x2 << "," << new_y2;

  return new_d.str();
}

Point FindIntersecionWithRectangle(const std::string &path,
                                   double rect_x,
                                   double rect_y,
                                   double rect_width,
                                   double rect_height)
{
  const auto points = GetFirstTwoPoints(path);

  if (points.size() < 2)
  {
    return {};
  }
  const auto path_start = points.at(0);
  const auto path_end = points.at(1);

  // Krawędzie prostokąta: lewa, prawa, górna, dolna
  // Lewa krawędź
  if (MoreOrEqual(path_start.x, path_end.x))
  {
    if (const auto intersection =
            utils::geometry::GetIntersectionPoint(path_start.x,
                                                  path_start.y,
                                                  path_end.x,
                                                  path_end.y,
                                                  rect_x,
                                                  rect_y,
                                                  rect_x,
                                                  rect_y + rect_height))
    {
      if ((AreEqual(intersection.value().x, rect_x) &&
           MoreOrEqual(intersection.value().y, rect_y) &&
           LessOrEqual(intersection.value().y, rect_y + rect_height)) ||
          (AreEqual(intersection.value().y, rect_y) &&
           MoreOrEqual(intersection.value().x, rect_x) &&
           LessOrEqual(intersection.value().x, rect_x + rect_width)) ||
          (AreEqual(intersection.value().y, rect_y + rect_height) &&
           MoreOrEqual(intersection.value().x, rect_x) &&
           LessOrEqual(intersection.value().x, rect_x + rect_width)))
      {
        return intersection.value();
      }
    }
  }

  // Prawa krawędź
  if (LessOrEqual(path_start.x, path_end.x))
  {
    if (const auto intersection =
            utils::geometry::GetIntersectionPoint(path_start.x,
                                                  path_start.y,
                                                  path_end.x,
                                                  path_end.y,
                                                  rect_x + rect_width,
                                                  rect_y,
                                                  rect_x + rect_width,
                                                  rect_y + rect_height))
    {
      if ((AreEqual(intersection.value().x, rect_x + rect_width) &&
           MoreOrEqual(intersection.value().y, rect_y) &&
           LessOrEqual(intersection.value().y, rect_y + rect_height)) ||
          (AreEqual(intersection.value().y, rect_y) &&
           MoreOrEqual(intersection.value().x, rect_x) &&
           LessOrEqual(intersection.value().x, rect_x + rect_width)) ||
          (AreEqual(intersection.value().y, rect_y + rect_height) &&
           MoreOrEqual(intersection.value().x, rect_x) &&
           LessOrEqual(intersection.value().x, rect_x + rect_width)))
      {
        return intersection.value();
      }
    }
  }

  // Górna krawMoreOrEqual(ędź
  if (MoreOrEqual(path_start.y, path_end.y))
  {
    if (const auto intersection =
            utils::geometry::GetIntersectionPoint(path_start.x,
                                                  path_start.y,
                                                  path_end.x,
                                                  path_end.y,
                                                  rect_x,
                                                  rect_y,
                                                  rect_x + rect_width,
                                                  rect_y))
    {
      if ((AreEqual(intersection.value().y, rect_y) &&
           MoreOrEqual(intersection.value().x, rect_x) &&
           LessOrEqual(intersection.value().x, rect_x + rect_width)) ||
          (AreEqual(intersection.value().x, rect_x) &&
           MoreOrEqual(intersection.value().y, rect_y) &&
           LessOrEqual(intersection.value().y, rect_y + rect_height)) ||
          (AreEqual(intersection.value().x, rect_x + rect_width) &&
           MoreOrEqual(intersection.value().y, rect_y) &&
           LessOrEqual(intersection.value().y, rect_y + rect_height)))
      {
        return intersection.value();
      }
    }
  }

  // Dolna krawędź
  if (LessOrEqual(path_start.y, path_end.y))
  {
    if (const auto intersection =
            utils::geometry::GetIntersectionPoint(path_start.x,
                                                  path_start.y,
                                                  path_end.x,
                                                  path_end.y,
                                                  rect_x,
                                                  rect_y + rect_height,
                                                  rect_x + rect_width,
                                                  rect_y + rect_height))
    {
      if ((AreEqual(intersection.value().y, rect_y + rect_height) &&
           MoreOrEqual(intersection.value().x, rect_x) &&
           LessOrEqual(intersection.value().x, rect_x + rect_width)) ||
          (AreEqual(intersection.value().x, rect_x) &&
           MoreOrEqual(intersection.value().y, rect_y) &&
           LessOrEqual(intersection.value().y, rect_y + rect_height)) ||
          (AreEqual(intersection.value().x, rect_x + rect_width) &&
           MoreOrEqual(intersection.value().y, rect_y) &&
           LessOrEqual(intersection.value().y, rect_y + rect_height)))
      {
        return intersection.value();
      }
    }
  }

  return {};
}

std::string UpdateToStartOnRectangleBorder(const std::string &path,
                                           double rect_x,
                                           double rect_y,
                                           double rect_width,
                                           double rect_height)
{
  const auto new_starting_point = FindIntersecionWithRectangle(
      path, rect_x, rect_y, rect_width, rect_height);
  return UpdateFirstPoint(path, new_starting_point);
}

} // namespace path
} // namespace svg
} // namespace helpers
