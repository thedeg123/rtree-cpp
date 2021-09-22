#pragma once

#include <vector>
#include <string>

class Location
{
public:
  std::vector<double> box;
  std::string name;
  Location(std::string name, std::vector<double> box);
  void printLocation();
};