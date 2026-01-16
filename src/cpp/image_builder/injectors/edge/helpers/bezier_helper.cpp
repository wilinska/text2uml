#include "src/cpp/image_builder/injectors/edge/helpers/path_helper.hpp"
#include "src/cpp/utils/geometry/point.hpp"
#include "src/cpp/utils/geometry/utils.hpp"
#include <iostream>
#include <regex>
#include <sstream>

namespace helpers
{
namespace svg
{
namespace bezier
{

struct Point
{
  double x, y;
  Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

// Funkcja obliczająca punkty kontrolne dla krzywej Béziera
std::pair<Point, Point> CalculateControlPoints(const Point &p0, const Point &p1)
{
  // Proste podejście: punkty kontrolne na 1/3 i 2/3 odległości z przesunięciem
  double dx = (p1.x - p0.x) / 3.0;
  double dy = (p1.y - p0.y) / 3.0;
  Point ctrl1(p0.x + dx, p0.y + dy * 1.5); // Przesunięcie dla zaokrąglenia
  Point ctrl2(p0.x + 2 * dx, p0.y + dy * 0.5); // Przesunięcie dla zaokrąglenia
  return {ctrl1, ctrl2};
}

// Funkcja zamieniająca polilinię na krzywą Béziera
std::string PolylineToBezier(const std::string &path_data)
{
  std::vector<Point> points;
  std::regex point_regex("[ML]\\s*(\\d+\\.?\\d*),(\\d+\\.?\\d*)");
  auto matches =
      std::sregex_iterator(path_data.begin(), path_data.end(), point_regex);
  auto end = std::sregex_iterator();

  for (auto it = matches; it != end; ++it)
  {
    double x = std::stod((*it)[1].str());
    double y = std::stod((*it)[2].str());
    points.emplace_back(x, y);
  }

  if (points.size() < 2)
    return path_data; // Nic do zaokrąglenia

  std::ostringstream new_path;
  new_path << "M" << points[0].x << "," << points[0].y;
  for (size_t i = 1; i < points.size(); ++i)
  {
    auto [ctrl1, ctrl2] = CalculateControlPoints(points[i - 1], points[i]);
    new_path << " C" << ctrl1.x << "," << ctrl1.y << " " << ctrl2.x << ","
             << ctrl2.y << " " << points[i].x << "," << points[i].y;
  }
  return new_path.str();
}

Point CalculateQuadraticControlPoint(const Point &p0, const Point &p1)
{
  double dx = (p1.x - p0.x) / 2.0;
  double dy = (p1.y - p0.y) / 2.0;
  return Point(p0.x + dx, p0.y + dy * 1.5); // Przesunięcie dla zaokrąglenia
}

// Funkcja obliczająca dwa punkty kontrolne dla kubicznej krzywej Béziera
std::pair<Point, Point> CalculateCubicControlPoints(const Point &p0,
                                                    const Point &p1)
{
  double dx = (p1.x - p0.x) / 3.0;
  double dy = (p1.y - p0.y) / 3.0;
  Point ctrl1(p0.x + dx, p0.y + dy * 1.5); // Przesunięcie dla zaokrąglenia
  Point ctrl2(p0.x + 2 * dx, p0.y + dy * 0.5); // Przesunięcie dla zaokrąglenia
  return {ctrl1, ctrl2};
}

// Funkcja zamieniająca polilinię na krzywą Béziera
std::string CreatePolylineToBezier(const std::string &path_data)
{
  std::vector<Point> points;
  std::regex point_regex("[ML]\\s*(\\d+\\.?\\d*),(\\d+\\.?\\d*)");
  auto matches =
      std::sregex_iterator(path_data.begin(), path_data.end(), point_regex);
  auto end = std::sregex_iterator();

  double last_x = -1;
  double last_y = -1;
  for (auto it = matches; it != end; ++it)
  {
    double x = std::stod((*it)[1].str());
    double y = std::stod((*it)[2].str());

    if (last_x != x || last_y != y)
    {
      points.emplace_back(x, y);
      last_x = x;
      last_y = y;
    }
  }

  if (points.size() < 2)
    return path_data; // Nic do zaokrąglenia

  std::ostringstream new_path;
  new_path << "M " << points[0].x << "," << points[0].y;

  if (points.size() == 2)
  {
    // Użyj kwadratowej krzywej Béziera dla dokładnie 2 punktów
    Point ctrl = CalculateQuadraticControlPoint(points[0], points[1]);
    new_path << " Q " << ctrl.x << "," << ctrl.y << " " << points[1].x << ","
             << points[1].y;
  }
  else
  {
    // Użyj kubicznej krzywej Béziera dla więcej niż 2 punktów
    for (size_t i = 1; i < points.size(); ++i)
    {
      auto [ctrl1, ctrl2] =
          CalculateCubicControlPoints(points[i - 1], points[i]);
      new_path << " C " << ctrl1.x << "," << ctrl1.y << " " << ctrl2.x << ","
               << ctrl2.y << " " << points[i].x << "," << points[i].y;
    }
  }

  return new_path.str();
}

// Parsowanie ciągu "d" i ekstrakcja punktów
std::vector<Point> parsePathD(const std::string &d)
{
  std::vector<Point> points;
  std::stringstream ss(d);
  char command;
  float x, y, last_x, last_y;
  bool firstMove = true;

  while (ss >> command)
  {
    if (command == 'M' || command == 'L')
    {
      ss >> x;
      ss.ignore(1); // Ignoruj przecinek
      ss >> y;
      if (command == 'M' && firstMove)
      {
        points.emplace_back(x, y);
        firstMove = false;
        last_x = x;
        last_y = y;
      }
      else if (!firstMove && command == 'L' && (x != last_x || y != last_y))
      {
        points.emplace_back(x, y);
        last_x = x;
        last_y = y;
      }
    }
  }
  return points;
}

// Konwersja polyline na Béziera
std::string convertToBezier(const std::vector<Point> &points,
                            const bool bend_single_line)
{
  if (points.size() < 2)
    return "";

  std::stringstream bezier;
  bezier << "M " << points[0].x << "," << points[0].y; // Punkt startowy

  if (points.size() == 2)
  {
    if (bend_single_line)
    {
      for (size_t i = 1; i < points.size(); ++i)
      {
        auto [ctrl1, ctrl2] =
            CalculateCubicControlPoints(points[i - 1], points[i]);
        bezier << " C " << ctrl1.x << "," << ctrl1.y << " " << ctrl2.x << ","
               << ctrl2.y << " " << points[i].x << "," << points[i].y;
      }
    }
    else
    {
      bezier << " L " << points[1].x << "," << points[1].y;
    }
  }
  else
  {
    // Więcej niż 2 punkty - konwersja na Béziera jak wcześniej
    for (size_t i = 1; i < points.size() - 1; i += 2)
    {
      if (i + 2 < points.size())
      {
        // Użyj punktów pośrednich jako punktów kontrolnych (kubiczna C)
        bezier << " C " << points[i].x << "," << points[i].y
               << " " // Punkt kontrolny 1
               << points[i + 1].x << "," << points[i + 1].y
               << " " // Punkt kontrolny 2
               << points[i + 2].x << "," << points[i + 2].y; // Punkt końcowy
      }
      else if (i + 1 < points.size())
      {
        // Ostatni segment z jednym punktem kontrolnym (kwadratowa Q)
        bezier << " Q " << points[i].x << "," << points[i].y
               << " "                                        // Punkt kontrolny
               << points[i + 1].x << "," << points[i + 1].y; // Punkt końcowy
      }
    }
  }
  return bezier.str();
}

std::string PolylineToBezierOnExistingPoints(const std::string &path_data)
{
  std::vector<Point> points = parsePathD(path_data);
  std::string bezierD = convertToBezier(points, false);
  return bezierD;
}

} // namespace bezier
} // namespace svg
} // namespace helpers
