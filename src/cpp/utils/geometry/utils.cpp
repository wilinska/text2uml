#include "src/cpp/utils/geometry/point.hpp"
#include <iostream>
#include <optional>

namespace utils
{
namespace geometry
{

std::optional<Point> GetIntersectionPoint(double x1,
                                          double y1,
                                          double x2,
                                          double y2,
                                          double x3,
                                          double y3,
                                          double x4,
                                          double y4,
                                          double &xi,
                                          double &yi)
{
  double denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  if (denom == 0)
  {
    return std::nullopt;
  }

  Point intersection{0, 0};

  intersection.x =
      ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
      denom;
  intersection.y =
      ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
      denom;

  xi = intersection.x;
  yi = intersection.y;

  return intersection;
}

std::optional<Point> GetIntersectionPoint(double x1,
                                          double y1,
                                          double x2,
                                          double y2,
                                          double x3,
                                          double y3,
                                          double x4,
                                          double y4)
{
  double denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  if (denom == 0)
  {
    return std::nullopt;
  }

  Point intersection{0, 0};

  intersection.x =
      ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
      denom;
  intersection.y =
      ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
      denom;

  return intersection;
}

} // namespace geometry
} // namespace utils
