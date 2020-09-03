#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

int check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x,y)!=expected_ans){
    printf("fail to pass the test");
    return 0;
  }
  return 1;
}

int main(void) {
  int check_index = check(0,0,1) * check(2147483648, 1, 2147483648) * check(2, 3, 8);
  if (check_index == 0) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

