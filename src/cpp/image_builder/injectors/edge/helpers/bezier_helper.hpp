#ifndef SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_HELPERS_BEZIER_HELPER_HPP
#define SRC_CPP_IMAGE_BUILDER_INJECTORS_EDGE_HELPERS_BEZIER_HELPER_HPP

#include <string>

namespace helpers
{
namespace svg
{
namespace bezier
{
std::string PolylineToBezier(const std::string &path_data);
std::string PolylineToBezierOnExistingPoints(const std::string &path_data);
} // namespace bezier
} // namespace svg
} // namespace helpers

#endif
