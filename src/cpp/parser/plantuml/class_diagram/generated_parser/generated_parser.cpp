#include <iostream>
#include <sstream>

namespace class_diagram
{
namespace generated_parser
{
std::string last_error_report;

void FillLastError(std::string error_report)
{
  last_error_report = error_report;
}

std::string GetLastError() { return last_error_report; }

} // namespace generated_parser
} // namespace class_diagram