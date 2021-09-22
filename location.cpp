#include "location.hpp"
#include "print.hpp"

Location::Location(std::string name, std::vector<double> box) : name(name), box(box){};
Location::Location() : name(""), box(std::vector<double>(0.0, 0.0)){};
Location::~Location()
{
  print("deleting");
  for (auto child = children.begin(); child < children.end(); child++)
    delete *child;
}

bool Location::isLeaf() { return children.size() == 0; }

void Location::printLocation()
{
  std::cout << "Location named: " << name << " and coordinates: ";
  for (auto i : box)
    std::cout << i << ", ";
  std::cout << std::endl;
}