#pragma once

#include <vector>
#include <string>

class Location
{
public:
  std::vector<double[2]> box;
  std::string name;
  std::vector<Location *> children;
  Location();
  ~Location();
  Location::Location(std::string name, std::vector<double[2]> box);
  void printLocation();
  bool isLeaf();
  double area();
};