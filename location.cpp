#include "location.hpp"
#include "print.hpp"

Location::Location(std::string name, std::vector<double> box) : name(name), box(box){};

void Location::printLocation()
{
  std::cout << "Location named: " << name << " and coordinates: ";
  for (auto i : box)
    std::cout << i << ", ";
  std::cout << std::endl;
}