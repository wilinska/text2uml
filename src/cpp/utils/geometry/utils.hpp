#ifndef SRC_CPP_UTILS_GEOMETRY_UTILS_HPP
#define SRC_CPP_UTILS_GEOMETRY_UTILS_HPP

#include "src/cpp/utils/geometry/point.hpp"
#include <optional>
#include <ostream>

namespace utils
{
namespace geometry
{

class LinearFunction
{
  LinearFunction(const Point &p1, const Point &p2)
      : slope_{(p2.y - p1.y) / (p2.x - p1.x)},
        intercept_{p1.y - slope_ * p1.x}
  {
  }

  double operator()(double arg, bool reversed = false) const
  {
    if (reversed)
    {
      return slope_ * arg + intercept_;
    }
    return (arg - intercept_) / slope_;
  }

private:
  const double slope_;
  const double intercept_;
};

std::optional<Point> GetIntersectionPoint(double x1,
                                          double y1,
                                          double x2,
                                          double y2,
                                          double x3,
                                          double y3,
                                          double x4,
                                          double y4,
                                          double &xi,
                                          double &yi);

std::optional<Point> GetIntersectionPoint(double x1,
                                          double y1,
                                          double x2,
                                          double y2,
                                          double x3,
                                          double y3,
                                          double x4,
                                          double y4);

} // namespace geometry
} // namespace utils

#endif // SRC_CPP_UTILS_GEOMETRY_UTILS_HPP
