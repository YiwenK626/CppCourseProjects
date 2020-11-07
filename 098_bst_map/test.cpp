#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "bstmap.h"

int main() {
  BstMap<int, int> b;
  b.add(15, 15);
  b.add(2, 2);
  b.add(13, 13);
  b.add(17, 17);
  b.add(1, 1);
  b.add(3, 3);
  b.add(14, 14);

  assert(b.lookup(3) == 3);
  b.remove(2);
  assert(b.lookup(13) == 13);

  BstMap<int, int> b2 = b;

  assert(b.lookup(17) == 17);
  return EXIT_SUCCESS;
}
