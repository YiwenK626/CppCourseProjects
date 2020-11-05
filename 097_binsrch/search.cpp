#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int ans = checkMid(f, low, high);
  return ans;
}

int checkMid(Function<int, int> * f, int low, int high) {
  int mid;
  mid = (low + high) / 2;
  while (high - low > 1) {
    int mval = f->invoke(mid);

    if (mval > 0) {
      return checkMid(f, low, mid);
    }
    else {
      return checkMid(f, mid, high);
    }
  }
  return low;
}
