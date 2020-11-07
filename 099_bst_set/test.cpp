#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "bstset.h"

int main() {
  BstSet<int> b;
  b.add(15);
  b.add(2);
  b.add(13);
  b.add(17);
  b.add(1);
  b.add(3);
  b.add(14);

  assert(b.contains(3));
  b.remove(2);
  assert(!b.contains(2));

  BstSet<int> b2 = b;

  assert(b.contains(17));
  return EXIT_SUCCESS;
}
