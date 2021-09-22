#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "print.hpp"
#include <stdlib.h>
#include "location.hpp"

std::vector<std::string> tokenize(std::string s, std::string del = ",")
{
  int start = 0;
  std::vector<std::string> ret;
  int end = s.find(del);
  while (end != -1)
  {
    ret.push_back(s.substr(start, end - start));
    start = end + del.size();
    end = s.find(del, start);
  }
  ret.push_back(s.substr(start, end - start));
  return ret;
}

void processFile(char *filename)
{
  std::ifstream myfile;
  myfile.open(filename);
  if (myfile.is_open())
  {
    std::string line;
    while (myfile >> line)
    {
      auto vec = tokenize(line, ",");
      std::vector<double> points;
      for (auto n = vec.begin() + 1; n < vec.end(); n++)
        points.push_back(std::stod(*n));
      Location l = Location(vec[0], points);
      l.printLocation();
    }
  }
}
