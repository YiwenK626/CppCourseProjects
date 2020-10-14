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

  FILE * lib = fopen(argv[1], "r");  // import files for car libraty and story template
  FILE * template = fopen(argv[2], "r");
  if (lib == NULL || template == NULL) {
    perror("NULL input");
    exit(EXIT_FAILURE);
  }

  catarray_t * cats = malloc(sizeof(*cats));
  creatCats(lib, cats);          //create a catearray
  parseTemp(template, cats, 0);  //parse the template
  freeCatArr(cats, cats->n);     // free the catearray created
  return 0;
}
