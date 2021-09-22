#include "rtree.hpp"

int main(int argc, char **argv)
{
  RTree t;
  if (argc > 1)
    t.loadTree(argv[1]);
  t.printTree();
  return 0;
}