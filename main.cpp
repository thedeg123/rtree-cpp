#include "processfile.h"

int main(int argc, char **argv)
{
  if (argc > 1)
    processFile(argv[1]);
  return 0;
}