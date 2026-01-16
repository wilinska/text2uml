#ifndef SRC_CPP_PARSER_PLANTUML_HELPERS_HELPERS_HPP
#define SRC_CPP_PARSER_PLANTUML_HELPERS_HELPERS_HPP

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>

std::tuple<double, double> extractCoordinates(const std::string &input);

#endif // SRC_CPP_PARSER_PLANTUML_HELPERS_HELPERS_HPP
