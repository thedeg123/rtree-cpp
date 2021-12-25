#include "location.hpp"
#include "print.hpp"

Location::Location(std::string name, std::vector<double[2]> box) : name(name), box(box){};
Location::Location() : name(""),
                       box(std::vector<double[2]>()){};
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
  for (auto dim = box.begin(); dim < box.end(); dim++)
  {
    std::cout << dim[0] << ", " << dim[1] << ", ";
  }
  std::cout << std::endl;
}

double Location::area()
{
  if (box.size() == 0)
  {
    return 0.0;
  }
  auto dimension = box[0];
  double area = 0;
  for (auto dim = box.begin() + 1; dim < box.end(); dim++)
  {
    area *= std::abs(dim[1] - dim[0]);
  }
  return area;
}