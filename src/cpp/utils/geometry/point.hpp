#ifndef SRC_CPP_UTILS_GEOMETRY_POINT_HPP
#define SRC_CPP_UTILS_GEOMETRY_POINT_HPP

#include <ostream>

namespace utils
{
namespace geometry
{

struct Point
{
  double x;
  double y;

  Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

  bool operator==(const Point &other) const
  {
    return x == other.x && y == other.y;
  }

  friend std::ostream &operator<<(std::ostream &os, const Point &p)
  {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
};

} // namespace geometry
} // namespace utils

#endif // SRC_CPP_UTILS_GEOMETRY_POINT_HPP
