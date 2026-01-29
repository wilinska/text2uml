#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_HELPERS_PATH_HELPER_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_HELPERS_PATH_HELPER_HPP

#include "src/cpp/utils/geometry/point.hpp"
#include <string>
#include <vector>

namespace helpers
{
namespace svg
{
namespace path
{

namespace path_helpers
{
std::string
shortenPath(const std::string &pathData, double shortenBy, bool start);

}

using Point = utils::geometry::Point;

std::vector<Point> GetFirstTwoPoints(const std::string &path);

std::string UpdateFirstPoint(const std::string &path, const Point &point);
std::string Shorten(const std::string &path, const double shortening);
std::string UpdateToStartOnRectangleBorder(const std::string &path,
                                           double rect_x,
                                           double rect_y,
                                           double rect_width,
                                           double rect_height);

std::string
MovePath(const std::string &path_data, int dx, int dy, bool isSource);

Point GetPointAlongPath(const std::string &path, double percentage);

} // namespace path
} // namespace svg
} // namespace helpers

#endif
