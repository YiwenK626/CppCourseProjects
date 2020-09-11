#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  int ind = 1;
  int mem = 1;
  for (unsigned int i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      ind++;
    }
    else {
      mem = max(mem, ind);
      ind = 1;
    }
  }
  mem = max(mem, ind);
  return mem;
}
