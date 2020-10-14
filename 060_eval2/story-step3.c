#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "invalid number of inputs for step3\n");
    exit(EXIT_FAILURE);
  }

  FILE * lib = fopen(argv[1], "r");
  FILE * template = fopen(argv[2], "r");
  if (lib == NULL || template == NULL) {
    perror("NULL input");
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = malloc(sizeof(*cats));
  creatCats(lib, cats);
  parseTemp(template, cats, 0);
  freeCatArr(cats, cats->n);
  return 0;
}
