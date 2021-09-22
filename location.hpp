#pragma once

#include <vector>
#include <string>

class Location
{
public:
  std::vector<double> box;
  std::string name;
  std::vector<Location *> children;
  Location();
  ~Location();
  Location(std::string name, std::vector<double> box);
  void printLocation();
  bool isLeaf();
};