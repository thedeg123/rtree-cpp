#pragma once
#include "location.hpp"
#include "string"
#include "vector"
#include "tuple"

class RTree
{
public:
  int dimensionality;
  RTree();
  RTree(int dimensions);
  RTree(int dimensions, char *filename);
  ~RTree();
  void insertNode(std::string name, std::vector<double> &box);
  bool loadTree(char *filename);
  void printTree();

private:
  static const int MAX_ENTRIES = 10;
  static const int MIN_ENTRIES = MAX_ENTRIES / 2;
  Location *tree;
  std::tuple<Location *, Location *> splitNode(Location *node);
  std::tuple<Location *, Location *> pickSeeds(std::vector<Location *> &children);
  Location *chooseLeaf(Location *node, std::vector<double> &newBox);
  double findCombinedArea(std::vector<double> &box1, std::vector<double> &box2);
  double findEnlarge(std::vector<double> &box1, std::vector<double> &box2);
  void printTree(Location *node);
  std::vector<std::string> tokenize(std::string s, std::string del);
};