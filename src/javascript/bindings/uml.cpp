#include <emscripten/bind.h>

#include "src/cpp/generator.hpp"

using namespace emscripten;
using namespace Text2UML;

EMSCRIPTEN_BINDINGS(Text2UML)
{
  emscripten::class_<Generator>("Generator")
      .constructor<>()
      .class_function("Generate", &Generator::Generate);
}
