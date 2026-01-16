#ifndef SRC_CPP_GRAPH_OBJECT_HPP
#define SRC_CPP_GRAPH_OBJECT_HPP

#include <map>
#include <string>

class Object
{
public:
  std::uint64_t id;
  std::map<std::string, std::string> graphics;
  std::map<std::string, std::string> attributes;

  Object() = default;

  Object(std::uint64_t id,
         std::map<std::string, std::string> graphics,
         std::map<std::string, std::string> attributes)
      : id(id),
        graphics(graphics),
        attributes(attributes)
  {
  }

  virtual ~Object() = default;
};

#endif // SRC_CPP_GRAPH_OBJECT_HPP
