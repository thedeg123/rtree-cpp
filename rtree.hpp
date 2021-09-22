#pragma once
#include "location.hpp"
#include "string"
#include "vector"

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
  Location *chooseLeaf(Location *node, std::vector<double> &newBox);
  double findEnlarge(std::vector<double> &box1, std::vector<double> &box2);
  void printTree(Location *node);
  std::vector<std::string> tokenize(std::string s, std::string del);
};