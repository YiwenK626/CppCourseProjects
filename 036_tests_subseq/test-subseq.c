#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int test(int * array, size_t n, size_t ans) {
  if (maxSeq(array, n) != ans) {
    printf("fail to pass the test");
    return 0;
  }
  return 1;
}

int main() {
  int myArray1[] = {1, 3, 2, 4};
  int myArray2[] = {1, 1, 2, 3};
  int myArray3[] = {-1,2,6};
  int myArray4[] = {-3,-2,-1};
  int myArray5[] = {1,1};
  int myArray7[] = {};

  int ind = test(myArray1,4,2) * test(myArray3,3,3) * test(myArray2, 4, 3) * test(myArray4, 3, 3) \
  * test(myArray5, 2, 1) *test(myArray7, 0, 0);
  if (ind == 0) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
