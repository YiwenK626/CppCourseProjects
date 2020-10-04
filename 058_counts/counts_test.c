#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 12
int main(void) {
  char * testData[NUM_TESTS] = {"A",
                                "banana",
                                "A",
                                "apple",
                                "frog",
                                "sword",
                                "bear",
                                "8",
                                "frog",
                                "apple",
                                "zebra",
                                "knight"};
  counts_t * testCounts = createCounts();
  for (int i = 0; i < NUM_TESTS; i++) {
    addCount(testCounts, testData[i]);
  }
  printCounts(testCounts, stdout);
  freeCounts(testCounts);
  return EXIT_SUCCESS;
}
