
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <tuple>

#include "rtree.hpp"
#include "location.hpp"
#include "print.hpp"

RTree::RTree() : dimensionality(2){};
RTree::RTree(int dimensions) : dimensionality(dimensions){};
RTree::RTree(int dimensions, char *filename) : dimensionality(dimensions)
{
  loadTree(filename);
};
RTree::~RTree()
{
  delete tree;
}

void RTree::printTree()
{
  return printTree(tree);
}

void RTree::printTree(Location *node)
{
  node->printLocation();
  for (auto child = node->children.begin(); child < node->children.end(); child++)
  {
    printTree(*child);
  }
}

bool RTree::loadTree(char *filename)
{
  std::ifstream myfile(filename);
  if (!myfile.is_open())
  {
    throw std::invalid_argument("Failed to open supplied file");
    return false;
  }
  std::string line;
  while (myfile >> line)
  {
    auto vec = tokenize(line, ",");
    std::vector<double> points;
    for (auto n = vec.begin() + 1; n < vec.end(); n++)
      points.push_back(std::stod(*n));
    if (points.size() != dimensionality)
    {
      throw std::invalid_argument("Dimensionality must match supplied data");
    }
    insertNode(vec[0], points);
  };
  return true;
};

void RTree::insertNode(std::string name, std::vector<double> &box)
{
  if (tree == NULL)
  {
    tree = new Location(name, box);
    return;
  }
  else
  {

    Location *parent = chooseLeaf(tree, box);
    Location *newNode = new Location(name, box);
    parent->children.push_back(newNode);
    if (parent->children.size() > MAX_ENTRIES)
    {
      auto parents = splitNode(parent);
    }
    else
    {
    }
  }
}

std::tuple<Location *, Location *> RTree::splitNode(Location *node)
{
  std::vector<Location *> group1, group2;
  auto seeds = pickSeeds(node->children);
}

std::tuple<Location *, Location *> RTree::pickSeeds(std::vector<Location *> &children)
{
  double waste = 0;
  std::tuple<Location *, Location *> worstPair = {NULL,
                                                  NULL};
  for (auto node1 : children)
  {
    for (auto node2 : children)
    {
      if (node1 != node2)
      {

        double curwaste = findCombinedArea(node1->box, node2->box) - node1->area() - node2->area();
        if (curwaste > waste)
        {
          waste = curwaste;
          worstPair = {node1,
                       node2};
        }
      }
    }
  }
  return worstPair;
};

double RTree::findCombinedArea(std::vector<double> &box1, std::vector<double> &box2)
{
  if (box1.size() == 0 || box2.size() == 0)
  {
    return 0.0;
  }
  double area = std::max(box1[0], box2[0]) - std::min(box1[0], box2[0]);
  for (int i = 1; i < box1.size(); i++)
  {
    area *= (std::max(box1[i], box2[i]) - std::min(box1[i], box2[i]));
  }
  return area;
}

Location *
RTree::chooseLeaf(Location *node, std::vector<double> &newBox)
{
  if (node->isLeaf())
  {
    return node;
  }
  double minexpand = std::numeric_limits<double>::max();
  Location *parent = NULL;
  for (auto child : node->children)
  {
    double enlarge = findEnlarge(child->box, newBox);
    // TODO: if theres a tie we should take the one with less area
    if (enlarge < minexpand)
    {
      minexpand = enlarge;
      parent = child;
    }
  }
  return chooseLeaf(parent, newBox);
};

/**
 * @description Find how much you'd have to expand the area of `box1` by to accomidate `box2`
 * @return 
 */
double RTree::findEnlarge(std::vector<double> &box1, std::vector<double> &box2)
{
  double enlarge = 0;
  for (int i = 0; i < box1.size(); i++)
  {
    enlarge += (std::max(std::abs(box2[i]) - std::abs(box1[i]), 0.0));
  };
  return enlarge;
};

std::vector<std::string> RTree::tokenize(std::string s, std::string del = ",")
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
};
